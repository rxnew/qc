#include "qo.hpp"

namespace qc {
namespace io {
Qo::Messages Qo::_err_msgs = {
  "Illegal format of gates. Too many or few parameters.",
  "Illegal format of gates. Gate name contains spaces.",
  "Illegal format of gates. Contorol and target bits is empty.",
  "Illegal format of gates. Bit is not numberic.",
  "Illegal format of gates. Unknown gate name."
};

auto Qo::_divideIntoGroups(const std::string& line)
  throw(IfExc) -> strings {
  auto groups = util::string::split(line, '\\', false);
  if(groups.size() != 4) throw IfExc(Qo::_err_msgs[0]);
  return std::move(groups);
}

auto Qo::_getGateString(const std::string& str)
  throw(IfExc) -> std::string {
  auto gate_strs = util::string::split(str);
  if(gate_strs.size() != 1) throw IfExc(Qo::_err_msgs[1]);
  return std::move(gate_strs.front());
}

auto Qo::_getBitStrings(const std::string& str)
  throw(IfExc) -> strings {
  auto bit_strs = util::string::split(str);
  if(bit_strs.empty()) throw IfExc(Qo::_err_msgs[2]);
  return std::move(bit_strs);
}

auto Qo::_getOptionStrings(const std::string& str)
  throw(IfExc) -> strings {
  auto option_strs = util::string::split(str);
  return std::move(option_strs);
}

auto Qo::_getCbit(const std::string& bit_str)
  throw(IfExc) -> Cbit {
  std::string bit_no = bit_str;
  bool polarity = true;
  if(bit_no[0] == '!') {
    bit_no = std::string(bit_no.cbegin() + 1, bit_no.cend());
    polarity = false;
  }
  if(!util::string::isNumeric(bit_no)) throw IfExc(Qo::_err_msgs[3]);
  return std::move(Cbit(static_cast<Bitno>(std::stoi(bit_no)), polarity));
}

auto Qo::_getTbit(const std::string& bit_str)
  throw(IfExc) -> Tbit {
  std::string bit_no = std::string(bit_str.cbegin() + 1, bit_str.cend());
  if(!util::string::isNumeric(bit_no)) throw IfExc(Qo::_err_msgs[3]);
  return std::move(Tbit(static_cast<Bitno>(std::stoi(bit_no))));
}

auto Qo::_getBits(const strings& bit_strs)
  throw(IfExc) -> BitListTuple {
  CbitList cbits;
  TbitList tbits;
  for(const auto& bit_str : bit_strs) {
    if(bit_str[0] == 'T') tbits.insert(Qo::_getTbit(bit_str));
    else                  cbits.insert(Qo::_getCbit(bit_str));
  }
  return std::move(std::make_tuple(cbits, tbits));
}

auto Qo::_getGate(const std::string& gate_str, const BitListTuple& bits)
  -> GatePtr {
  const CbitList& cbits = std::get<0>(bits);
  const TbitList& tbits = std::get<1>(bits);
  return std::move(GateBuilder::create(gate_str, cbits, tbits));
}

auto Qo::input(Circuit& circuit, const std::string& filename)
  throw(IfExc, std::ios_base::failure) -> void {
  std::ifstream ifs(filename);

  if(ifs.fail()) throw std::ios_base::failure("Cannot open file.");

  std::string line;
  while(getline(ifs, line)) {
    auto groups = Qo::_divideIntoGroups(line);

    auto gate_str = Qo::_getGateString(groups[0]);
    auto bit_strs = Qo::_getBitStrings(groups[1]);
    auto var_strs = Qo::_getOptionStrings(groups[2]);
    auto function_strs = Qo::_getOptionStrings(groups[3]);

    auto bits = Qo::_getBits(bit_strs);
    //auto vars = Qo::_getVariables(var_strs);
    //auto functions = Qo::_getFunctions(function_strs);

    //auto gate = Qo::_getGate(gate_str, bits, vars, functions);
    auto gate = Qo::_getGate(gate_str, bits);

    if(!gate) throw IfExc(Qo::_err_msgs[4]);
    circuit.addGate(gate);
  }
}
}
}
