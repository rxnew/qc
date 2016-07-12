#include "../esop.hpp"

#include "../../gate/library/x.hpp"

namespace qc {
namespace io {
std::string Esop::extension = ".esop";

Esop::Messages Esop::_err_msgs = {
  "Illegal format of headers. Too many or few columns.",
  "Illegal format of headers. Too many or few rows.",
  "Illegal format of headers. Unknown parameter.",
  "Illegal format of terms. Too many or few columns.",
  "Illegal format of terms. Too many or few rows.",
  "Illegal format of terms. Too many or few inputs or outputs.",
  "Illegal format of terms. Unknown parameter."
};

auto Esop::_setCount(Counts& counts, const std::string& line)
  throw(IfExc) -> void {
  auto data = util::string::split(line);
  if(data.size() != 2) throw IfExc(Esop::_err_msgs[0]);
  if(data[0] == ".i")      counts["input"]  = std::stoi(data[1]);
  else if(data[0] == ".o") counts["output"] = std::stoi(data[1]);
  else if(data[0] == ".p") counts["term"]   = std::stoi(data[1]);
  else if(data[0] != ".type" || data[1] != "esop") {
    throw IfExc(Esop::_err_msgs[2]);
  }
}

auto Esop::_getCounts(std::ifstream& ifs)
  throw(IfExc) -> Counts {
  Counts counts;
  std::string line;
  while(std::getline(ifs, line) && counts.size() < 3) {
    if(!Esop::_isCommentLine(line)) Esop::_setCount(counts, line);
  }
  if(counts.size() != 3) throw IfExc(Esop::_err_msgs[1]);
  return std::move(counts);
}

auto Esop::_getCbits(const std::string& str)
  throw(IfExc) -> CbitList {
  CbitList cbits;
  for(int i = 0; i < static_cast<int>(str.size()); i++) {
    if(str[i] == '1')      cbits.emplace(static_cast<Bitno>(i), true);
    else if(str[i] == '0') cbits.emplace(static_cast<Bitno>(i), false);
    else if(str[i] != '-') throw IfExc(Esop::_err_msgs[6]);
  }
  return std::move(cbits);
}

auto Esop::_getTbits(const std::string& str, int first)
  throw(IfExc) -> TbitList {
  TbitList tbits;
  for(int i = 0; i < static_cast<int>(str.size()); i++) {
    if(str[i] == '1') tbits.emplace(static_cast<Bitno>(i + first));
    else if(str[i] != '0') throw IfExc(Esop::_err_msgs[6]);
  }
  return std::move(tbits);
}

auto Esop::_getGate(const std::string& line, const Counts& counts)
  throw(IfExc) -> GatePtr {
  auto data = util::string::split(line);
  if(data.size() != 2) throw IfExc(Esop::_err_msgs[3]);
  if(data[0].size() != counts.at("input") ||
     data[1].size() != counts.at("output")) {
    throw IfExc(Esop::_err_msgs[5]);
  }
  auto cbits = Esop::_getCbits(data[0]);
  auto tbits = Esop::_getTbits(data[1], counts.at("input"));
  return std::move(GatePtr(new X(cbits, tbits)));
}

auto Esop::_print(const Gate& gate, std::ostream& os,
                  const std::set<Bitno>& inputs,
                  const std::set<Bitno>& outputs) -> void {
  assert(gate.getTypeName() == X::TYPE_NAME);
  for(const auto& input : inputs) {
    os << (!gate.isIncludedInCbitList(input) ? '-'
           : gate.getCbitPolarity(input)     ? '1'
           :                                   '0');
  }
  os << ' ';
  for(const auto& output : outputs) {
    os << (gate.isIncludedInTbitList(output) ? '1'
           :                                   '0');
  }
  os << std::endl;
}

auto Esop::_print(const Circuit& circuit, std::ostream& os) -> void {
  using util::container::ordered;
  auto inputs = ordered(qc::collectCbits(circuit));
  auto outputs = ordered(qc::collectTbits(circuit));
  os << ".i " << inputs.size() << std::endl;;
  os << ".o " << outputs.size() << std::endl;;
  os << ".p " << circuit.getGateCount() << std::endl;
  os << ".type esop" << std::endl;
  for(const auto& gate : circuit.getGateList()) {
    Esop::_print(*gate, os, inputs, outputs);
  }
  os << ".e" << std::endl;
}

auto Esop::input(Circuit& circuit, const std::string& filename)
  throw(IfExc, std::ios_base::failure) -> void {
  std::ifstream ifs(filename);

  if(ifs.fail()) throw std::ios_base::failure("Cannot open file.");

  auto counts = Esop::_getCounts(ifs);
  std::string line;
  while(std::getline(ifs, line)) {
    if(Esop::_isCommentLine(line)) continue;
    if(Esop::_isEndLine(line)) break;
    auto gate = Esop::_getGate(line, counts);
    assert(gate);
    circuit.addGate(gate);
  }

  if(counts["term"] != circuit.getGateCount()) {
    throw IfExc(Esop::_err_msgs[5]);
  }
}

auto Esop::output(const Circuit& circuit, const std::string& filename)
  throw(std::ios_base::failure) -> void {
  std::ofstream ofs(util::string::addExtension(filename, Esop::extension));
  if(ofs.fail()) throw std::ios_base::failure("Cannot open file.");
  Esop::print(circuit, ofs);
}
}
}
