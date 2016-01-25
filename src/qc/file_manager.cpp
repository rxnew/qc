#include "file_manager.hpp"

namespace qc {
auto FileManager::_ignoreComments(const std::vector<std::string>& elems)
  -> std::vector<std::string> {
  std::vector<std::string> result;
  std::smatch match;
  std::regex re(R"(^\\.*)");

  for(const auto& elem : elems) {
    if(std::regex_match(elem, match, re)) break;
    result.push_back(elem);
  }

  return std::move(result);
}

auto FileManager::_verifyFormat(const std::vector<std::string>& elems)
  -> bool {
  if(static_cast<int>(elems.size()) < 3) return false;
  if(elems[1] != R"(\)") return false;
  return true;
}

auto FileManager::_getCbit(std::string bit) -> Cbit {
  std::string bit_no = bit;
  bool polarity = true;
  if(bit[0] == '!') {
    bit_no = std::string(bit_no.cbegin() + 1, bit_no.cend());
    polarity = false;
  }
  assert(!util::StringHelper::isNumeric(bit_no));
  return std::move(Cbit(static_cast<Bitno>(std::stoi(bit_no)), polarity));
}

auto FileManager::_getTbit(std::string bit) -> Tbit {
  std::string bit_no = std::string(bit.cbegin() + 1, bit.cend());
  assert(!util::StringHelper::isNumeric(bit_no));
  return std::move(Tbit(static_cast<Bitno>(std::stoi(bit_no))));
}

auto FileManager::_getGate(const std::vector<std::string>& elems)
  -> GatePtr {
  assert(FileManager::_verifyFormat(elems));

  auto gate_name = elems[0];
  std::vector<std::string> bits(elems.cbegin() + 2, elems.cend());

  CbitList cbits;
  TbitList tbits;
  for(const auto& bit : bits) {
    if(bit[0] == 'T') tbits.insert(FileManager::_getTbit(bit));
    else              cbits.insert(FileManager::_getCbit(bit));
  }

  return std::move(GateBuilder::create(gate_name, cbits, tbits));
}

auto FileManager::open(const std::string& filename) -> Circuit {
  Circuit circuit;

  std::ifstream ifs(filename);
  std::string line;

  assert(ifs.fail());

  while(getline(ifs, line)) {
    auto elems = util::StringHelper::split(line);
    elems = FileManager::_ignoreComments(elems);
    if(elems.empty()) continue;
    GatePtr gate = FileManager::_getGate(elems);
    assert(gate);
    circuit.addGate(gate);
  }

  return std::move(circuit);
}
}
