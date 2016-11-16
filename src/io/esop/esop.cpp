#include "../esop.hpp"

#include "../../circuit.hpp"
#include "../../gate/library/x.hpp"
#include "../../util/container.hpp"
#include "../../util/string.hpp"

namespace qc {
namespace io {
auto Esop::input(Circuit& circuit, std::string const& filename)
  throw(IfExc, std::ios_base::failure) -> void {
  auto ifs = std::ifstream(filename);

  if(ifs.fail()) throw std::ios_base::failure("Cannot open file.");

  auto counts = _get_counts(ifs);
  auto line = std::string();
  while(std::getline(ifs, line)) {
    if(_is_comment_line(line)) continue;
    if(_is_end_line(line)) break;
    auto gate = _get_gate(line, counts);
    circuit.add_gate(std::move(gate));
  }

  if(counts["term"] != circuit.get_gates_count()) {
    throw IfExc(_err_msgs[5]);
  }
}

auto Esop::output(Circuit const& circuit, std::string const& filename)
  throw(std::ios_base::failure) -> void {
  auto ofs = std::ofstream(util::string::add_extension(filename, extension));
  if(ofs.fail()) throw std::ios_base::failure("Cannot open file.");
  print(circuit, ofs);
}

auto Esop::open(std::string const& filename)
  throw(IfExc, std::ios_base::failure) -> Circuit {
  auto const basename = util::string::basename(filename);
  auto circuit = Circuit(util::string::exclude_extension(basename));
  input(circuit, filename);
  return circuit;
}

auto Esop::print(Circuit const& circuit, std::ostream& os) -> void {
  assert(qc::is_esop_circuit(circuit));
  _print(circuit, os);
}

auto Esop::_is_comment_line(std::string const& line) -> bool {
  return line.front() == '#';
}

auto Esop::_is_end_line(std::string const& line) -> bool {
  return line == ".e";
}

auto Esop::_set_count(Counts& counts, std::string const& line)
  throw(IfExc) -> void {
  auto data = util::string::split(line);
  if(data.size() != 2) throw IfExc(_err_msgs[0]);
  if(data[0] == ".i")      counts["input"]  = std::stoi(data[1]);
  else if(data[0] == ".o") counts["output"] = std::stoi(data[1]);
  else if(data[0] == ".p") counts["term"]   = std::stoi(data[1]);
  else if(data[0] != ".type" || data[1] != "esop") {
    throw IfExc(_err_msgs[2]);
  }
}

auto Esop::_get_counts(std::ifstream& ifs)
  throw(IfExc) -> Counts {
  auto counts = Counts();
  auto line = std::string();
  while(std::getline(ifs, line) && counts.size() < 3u) {
    if(!_is_comment_line(line)) _set_count(counts, line);
  }
  if(counts.size() != 3u) throw IfExc(_err_msgs[1]);
  return counts;
}

auto Esop::_get_cbits(std::string const& str)
  throw(IfExc) -> CBits {
  auto cbits = CBits();
  for(auto i = 0u; i < str.size(); i++) {
    if(str[i] == '1')      cbits.emplace(static_cast<BitNo>(i), true);
    else if(str[i] == '0') cbits.emplace(static_cast<BitNo>(i), false);
    else if(str[i] != '-') throw IfExc(_err_msgs[6]);
  }
  return cbits;
}

auto Esop::_get_tbits(std::string const& str, int first)
  throw(IfExc) -> TBits {
  auto tbits = TBits();
  for(auto i = 0u; i < str.size(); i++) {
    if(str[i] == '1') tbits.emplace(static_cast<BitNo>(i + first));
    else if(str[i] != '0') throw IfExc(_err_msgs[6]);
  }
  return tbits;
}

auto Esop::_get_gate(std::string const& line, Counts const& counts)
  throw(IfExc) -> Gate {
  auto data = util::string::split(line);
  if(data.size() != 2) throw IfExc(_err_msgs[3]);
  if(data[0].size() != counts.at("input") ||
     data[1].size() != counts.at("output")) {
    throw IfExc(_err_msgs[5]);
  }
  auto cbits = _get_cbits(data[0]);
  auto tbits = _get_tbits(data[1], counts.at("input"));
  return Gate::make<X>(std::move(cbits), std::move(tbits));
}

auto Esop::_print(Gate const& gate, std::ostream& os,
                  std::set<BitNo> const& inputs,
                  std::set<BitNo> const& outputs) -> void {
  assert(gate.get_type_name() == X::TYPE_NAME);
  for(auto const& input : inputs) {
    os << (!gate.has_cbit(input)           ? '-'
           : gate.get_cbit_polarity(input) ? '1'
           :                                 '0');
  }
  os << ' ';
  for(auto const& output : outputs) {
    os << (gate.has_tbit(output) ? '1'
           :                       '0');
  }
  os << std::endl;
}

auto Esop::_print(Circuit const& circuit, std::ostream& os) -> void {
  auto inputs = util::container::ordered(collect_cbits(circuit));
  auto outputs = util::container::ordered(collect_tbits(circuit));
  os << ".i " << inputs.size() << std::endl;;
  os << ".o " << outputs.size() << std::endl;;
  os << ".p " << circuit.get_gates_count() << std::endl;
  os << ".type esop" << std::endl;
  for(auto const& gate : circuit.get_gates()) {
    _print(gate, os, inputs, outputs);
  }
  os << ".e" << std::endl;
}
}
}
