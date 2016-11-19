#include "../qo.hpp"

#include "../../gate/library.hpp"
#include "../../gate/group.hpp"
#include "../../circuit.hpp"
#include "../../util/string.hpp"

namespace qc {
namespace io {
constexpr Qo::Messages const Qo::_err_msgs = {
  "Illegal format of gates. Too many or few parameters.",
  "Illegal format of gates. Gate name contains spaces.",
  "Illegal format of gates. Contorol and target bits is empty.",
  "Illegal format of gates. Bit is not numberic.",
  "Illegal format of gates. Unknown gate name."
};

auto Qo::input(Circuit& circuit, std::string const& filename)
  throw(IfExc, std::ios_base::failure) -> void {
  auto ifs = std::ifstream(filename);
  if(ifs.fail()) throw std::ios_base::failure("Cannot open file.");
  circuit = _create_circuit(ifs);
}

auto Qo::output(Circuit const& circuit, std::string const& filename)
  throw(std::ios_base::failure) -> void {
  auto ofs = std::ofstream(util::string::add_extension(filename, extension));
  if(ofs.fail()) throw std::ios_base::failure("Cannot open file.");
  circuit.print(ofs);
}

auto Qo::open(std::string const& filename)
  throw(IfExc, std::ios_base::failure) -> Circuit {
  auto const basename = util::string::basename(filename);
  auto circuit = Circuit(util::string::exclude_extension(basename));
  input(circuit, filename);
  return circuit;
}

auto Qo::print(Circuit const& circuit, std::ostream& os) -> void {
  circuit.print(os);
}

auto Qo::_create_circuit(std::ifstream& ifs)
  throw(IfExc) -> Circuit {
  auto circuit = Circuit();
  auto line = std::string();
  while(getline(ifs, line)) {
    line = util::string::trim_comments(line, '#');
    line = util::string::trim_white_spaces(line);
    if(line == Group::BEGIN_TAG) {
      circuit.add_gate(_create_group(ifs));
    }
    else {
      circuit.add_gate(_create_gate(line));
    }
  }
  return circuit;
}

auto Qo::_create_group(std::ifstream& ifs)
  throw(IfExc) -> Gate {
  auto group = Group::make();
  auto line = std::string();
  while(getline(ifs, line)) {
    line = util::string::trim_comments(line, '#');
    line = util::string::trim_white_spaces(line);
    if(line == Group::END_TAG) break;
    group.add_gate(_create_gate(line));
  }
  return group;
}

auto Qo::_create_gate(std::string const& line)
  throw(IfExc) -> Gate {
  auto data = _divide_data(line);

  auto gate_str = _get_gate_string(data[0]);
  auto bit_strs = _get_bit_strings(data[1]);
  auto var_strs = _get_option_strings(data[2]);
  auto function_strs = _get_option_strings(data[3]);

  auto bits = _get_bits(bit_strs);
  //auto vars = _get_variables(var_strs);
  //auto functions = _get_functions(function_strs);

  //return _get_gate(gate_str, bits, vars, functions);
  return _get_gate(gate_str, bits);
}

auto Qo::_divide_data(std::string const& line)
  throw(IfExc) -> strings {
  auto data = util::string::split(line, '\\', false);
  if(data.size() != 4u) throw IfExc(_err_msgs[0]);
  return data;
}

auto Qo::_get_gate_string(std::string const& str)
  throw(IfExc) -> std::string {
  auto gate_strs = util::string::split(str);
  if(gate_strs.size() != 1u) throw IfExc(_err_msgs[1]);
  return std::move(gate_strs.front());
}

auto Qo::_get_bit_strings(std::string const& str)
  throw(IfExc) -> strings {
  auto bit_strs = util::string::split(str);
  if(bit_strs.empty()) throw IfExc(_err_msgs[2]);
  return bit_strs;
}

auto Qo::_get_option_strings(std::string const& str)
  throw(IfExc) -> strings {
  auto option_strs = util::string::split(str);
  return option_strs;
}

auto Qo::_get_cbit(std::string const& bit_str)
  throw(IfExc) -> CBit {
  auto bit_no = bit_str;
  auto polarity = true;
  if(bit_no[0] == '!') {
    bit_no = std::string(bit_no.cbegin() + 1, bit_no.cend());
    polarity = false;
  }
  if(!util::string::is_numeric(bit_no)) throw IfExc(_err_msgs[3]);
  return CBit(static_cast<BitNo>(std::stoi(bit_no)), polarity);
}

auto Qo::_get_tbit(std::string const& bit_str)
  throw(IfExc) -> TBit {
  auto const bit_no = std::string(bit_str.cbegin() + 1, bit_str.cend());
  if(!util::string::is_numeric(bit_no)) throw IfExc(_err_msgs[3]);
  return TBit(static_cast<BitNo>(std::stoi(bit_no)));
}

auto Qo::_get_bits(strings const& bit_strs)
  throw(IfExc) -> BitsTuple {
  auto cbits = CBits();
  auto tbits = TBits();
  for(auto const& bit_str : bit_strs) {
    if(bit_str[0] == 'T') tbits.insert(_get_tbit(bit_str));
    else                  cbits.insert(_get_cbit(bit_str));
  }
  return std::make_tuple(cbits, tbits);
}

auto Qo::_get_gate(std::string const& gate_str, BitsTuple const& bits)
  -> Gate {
  CBits const& cbits = std::get<0>(bits);
  TBits const& tbits = std::get<1>(bits);
  return make_gate(gate_str, cbits, tbits);
}
}
}
