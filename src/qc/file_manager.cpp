#include "file_manager.hpp"

namespace qc {
auto FileManager::_divideIntoGroups(const std::string& line) -> strings {
  auto groups = util::string::split(line, '\\', false);
  assert(static_cast<int>(groups.size()) == 4);
  return std::move(groups);
}

auto FileManager::_getGateString(const std::string& str) -> std::string {
  auto gate_strs = util::string::split(str);
  assert(static_cast<int>(gate_strs.size()) == 1);
  return std::move(gate_strs.front());
}

auto FileManager::_getBitStrings(const std::string& str) -> strings {
  auto bit_strs = util::string::split(str);
  assert(!bit_strs.empty());
  return std::move(bit_strs);
}

auto FileManager::_getOptionStrings(const std::string& str) -> strings {
  auto option_strs = util::string::split(str);
  return std::move(option_strs);
}

auto FileManager::_getCbit(const std::string& bit_str) -> Cbit {
  std::string bit_no = bit_str;
  bool polarity = true;
  if(bit_no[0] == '!') {
    bit_no = std::string(bit_no.cbegin() + 1, bit_no.cend());
    polarity = false;
  }
  assert(util::string::isNumeric(bit_no));
  return std::move(Cbit(static_cast<Bitno>(std::stoi(bit_no)), polarity));
}

auto FileManager::_getTbit(const std::string& bit_str) -> Tbit {
  std::string bit_no = std::string(bit_str.cbegin() + 1, bit_str.cend());
  assert(util::string::isNumeric(bit_no));
  return std::move(Tbit(static_cast<Bitno>(std::stoi(bit_no))));
}

auto FileManager::_getBits(const strings& bit_strs) -> BitListTuple {
  CbitList cbits;
  TbitList tbits;
  for(const auto& bit_str : bit_strs) {
    if(bit_str[0] == 'T') tbits.insert(FileManager::_getTbit(bit_str));
    else                  cbits.insert(FileManager::_getCbit(bit_str));
  }
  return std::move(std::make_tuple(cbits, tbits));
}

auto FileManager::_getGate(const std::string& gate_str, \
                           const BitListTuple& bits)
  -> GatePtr {
  const CbitList& cbits = std::get<0>(bits);
  const TbitList& tbits = std::get<1>(bits);
  return std::move(GateBuilder::create(gate_str, cbits, tbits));
}

auto FileManager::open(const std::string& filename) -> Circuit {
  Circuit circuit;

  std::ifstream ifs(filename);
  std::string line;

  assert(!ifs.fail());

  while(getline(ifs, line)) {
    auto groups = FileManager::_divideIntoGroups(line);

    auto gate_str = FileManager::_getGateString(groups[0]);
    auto bit_strs = FileManager::_getBitStrings(groups[1]);
    auto var_strs = FileManager::_getOptionStrings(groups[2]);
    auto function_strs = FileManager::_getOptionStrings(groups[3]);

    auto bits = FileManager::_getBits(bit_strs);
    //auto vars = FileManager::_getVariables(var_strs);
    //auto functions = FileManager::_getFunctions(function_strs);

    //auto gate = FileManager::_getGate(gate_str, bits, vars, functions);
    auto gate = FileManager::_getGate(gate_str, bits);

    assert(gate);
    circuit.addGate(gate);
  }

  return std::move(circuit);
}
}
