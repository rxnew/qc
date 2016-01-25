/**
 * @file circuit.cpp
 * @brief implementation of the quantum circuit class
 */

#include "circuit.hpp"

namespace qc {
/**
 * @fn Circuit()
 * @brief constructor
 * @detail empty Circuit class constructor
 */
Circuit::Circuit() {
}

/**
 * @fn Circuit(const Circuit& other)
 * @brief copy constructor
 * @param [in] other another Circuit class object
 */
Circuit::Circuit(const Circuit& other) {
  for(const auto& gate : other.gates_) {
    this->addGate(gate->clone());
  }
}

/**
 * @fn ~Circuit()
 * @brief destructor
 */
Circuit::~Circuit() {
  this->gates_.clear();
}

/**
 * @fn Circuit& operator=(const Circuit& other)
 * @brief assignment operator
 * @param [in] other another Circuit class object
 * @return reference to this object
 */
auto Circuit::operator=(const Circuit& other) -> Circuit& {
  for(const auto& gate : other.gates_) {
    this->addGate(gate->clone());
  }
  return *this;
}

/**
 * @fn bool operator==(const Circuit& other) const
 * @brief equality operator
 * @param [in] other another Circuit class object
 * @return true or false
 */
auto Circuit::operator==(const Circuit& other) const -> bool {
  if(this->gates_.size() != other.gates_.size()) return false;

  auto it = this->gates_.cbegin();
  auto jt = other.gates_.cbegin();
  while(it != this->gates_.cend() || jt != other.gates_.cend()) {
    if(**it != **jt) return false;
    it++, jt++;
  }

  return true;
}

/**
 * @fn bool operator!=(const Circuit& other) const
 * @brief nonequivalence operator
 * @param [in] other another Circuit class object
 * @return true or false
 */
auto Circuit::operator!=(const Circuit& other) const -> bool {
  return !(*this == other);
}

inline auto Circuit::append(const Circuit& circ) -> void {
  for(const auto& gate : circ.gates_) {
    this->addGate(gate->clone());
  }
}

auto Circuit::getAnyGate(int n) const -> GatePtr {
  int cnt = 0;
  for(const auto& gate_i : this->gates_) {
    if(cnt++ == n) return gate_i;
  }
  return GatePtr(nullptr);
}

auto Circuit::getGateIndex(const GatePtr& gate) const -> int {
  int cnt = 0;
  for(const auto& gate_i : this->gates_) {
    if(gate_i == gate) return cnt;
    cnt++;
  }
  return -1;
}

/**
 * @fn BitList getUsedBits() const
 * @brief take used bits of all included parallel quanutm gates
 * @return used bits
 */
auto Circuit::getUsedBits() const -> BitList {
  BitList used_bits;
  for(const auto& gate : this->gates_) {
    auto gate_used_bits = gate->getUsedBits();
    used_bits.insert(gate_used_bits.cbegin(), gate_used_bits.cend());
  }
  return std::move(used_bits);
}

auto Circuit::print(std::ostream& os) const -> void {
  for(const auto& gate : this->gates_) {
    gate->print(os);
  }
}

auto Circuit::FileManager::ignoreComments(const std::vector<std::string>& elems)
  -> std::vector<std::string> {
  std::vector<std::string> result;
  for(const auto& elem : elems) {
    if(elem == "\\\\") break;
    result.push_back(elem);
  }
  return std::move(result);
}

auto Circuit::FileManager::verifyFormat(const std::vector<std::string>& elems)
  -> bool {
  int size = static_cast<int>(elems.size());
  if(size < 3) return false;
  if(elems[1] != "\\") return false;
  return true;
}

auto Circuit::FileManager::getCbit(std::string bit) -> Cbit {
  std::string bit_no = bit;
  bool polarity = true;
  if(bit[0] == '!') {
    bit_no = std::string(bit_no.cbegin() + 1, bit_no.cend());
    polarity = false;
  }
  assert(!util::StringHelper::isNumeric(bit_no));
  return std::move(Cbit(static_cast<Bitno>(std::stoi(bit_no)), polarity));
}

auto Circuit::FileManager::getTbit(std::string bit) -> Tbit {
  std::string bit_no = std::string(bit.cbegin() + 1, bit.cend());
  assert(!util::StringHelper::isNumeric(bit_no));
  return std::move(Tbit(static_cast<Bitno>(std::stoi(bit_no))));
}

auto Circuit::FileManager::getGate(const std::vector<std::string>& elems)
  -> GatePtr {
  assert(Circuit::FileManager::verifyFormat(elems));
  auto gate_name = elems[0];
  std::vector<std::string> bits(elems.cbegin() + 2, elems.cend());
  CbitList cbits;
  TbitList tbits;
  for(const auto& bit : bits) {
    if(bit[0] == 'T') {
      tbits.insert(Circuit::FileManager::getTbit(bit));
    }
    else {
      cbits.insert(Circuit::FileManager::getCbit(bit));
    }
  }
  return std::move(GateBuilder::create(gate_name, cbits, tbits));
}

auto Circuit::FileManager::open(const std::string& filename) -> void {
  std::ifstream ifs(filename);
  std::string line;
  assert(ifs.fail());
  while(getline(ifs, line)) {
    auto elems = util::StringHelper::split(line);
    elems = Circuit::FileManager::ignoreComments(elems);
    if(elems.empty()) continue;
    GatePtr gate = Circuit::FileManager::getGate(elems);
  }
}
}
