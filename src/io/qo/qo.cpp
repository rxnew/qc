#include "../qo.hpp"

#include "../../gate/library.hpp"
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

  auto line = std::string();
  while(getline(ifs, line)) {
    auto groups = _divide_into_groups(line);

    auto gate_str = _get_gate_string(groups[0]);
    auto bit_strs = _get_bit_strings(groups[1]);
    auto var_strs = _get_option_strings(groups[2]);
    auto function_strs = _get_option_strings(groups[3]);

    auto bits = _get_bits(bit_strs);
    //auto vars = _getVariables(var_strs);
    //auto functions = _getFunctions(function_strs);

    //auto gate = _getGate(gate_str, bits, vars, functions);
    auto gate = _get_gate(gate_str, bits);

    circuit.add_gate(std::move(gate));
  }
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

auto Qo::_divide_into_groups(std::string const& line)
  throw(IfExc) -> strings {
  auto groups = util::string::split(line, '\\', false);
  if(groups.size() != 4u) throw IfExc(_err_msgs[0]);
  return groups;
}

auto Qo::_get_gate_string(std::string const& str)
  throw(IfExc) -> std::string {
  auto gate_strs = util::string::split(str);
  if(gate_strs.size() != 1) throw IfExc(_err_msgs[1]);
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
