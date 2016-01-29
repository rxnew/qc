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

auto Circuit::getMatrix() const -> Matrix {
  auto bits = util::container::convert<std::set>(this->getUsedBits());
  auto size = static_cast<size_t>(std::pow(2, bits.size()));
  auto result = util::eigen::identity(size);
  for(const auto& gate : this->gates_) {
    result = gate->getMatrix(bits) * result;
  }
  return std::move(result);
}

auto Circuit::print(std::ostream& os) const -> void {
  for(const auto& gate : this->gates_) {
    gate->print(os);
  }
}
}
