/**
 * @file circuit.cpp
 * @brief implementation of the quantum circuit class
 */

#include "../circuit.hpp"

namespace qc {
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
 * @fn BitList collectUsedBits() const
 * @brief take used bits of all included parallel quanutm gates
 * @return used bits
 */
auto Circuit::collectUsedBits() const -> BitList {
  BitList used_bits;
  for(const auto& gate : this->gates_) {
    auto gate_used_bits = gate->collectUsedBits();
    used_bits.insert(gate_used_bits.cbegin(), gate_used_bits.cend());
  }
  return std::move(used_bits);
}

auto Circuit::computeMatrix() const -> Matrix {
  auto ordered_bits = \
    util::container::convert<std::set>(this->collectUsedBits());
  auto size = static_cast<size_t>(std::pow(2, ordered_bits.size()));
  auto result = util::matrix::identity(size);
  for(const auto& gate : this->gates_) {
    result = gate->computeMatrix(ordered_bits) * result;
  }
  return std::move(result);
}

auto Circuit::simulate(const Vector& input) const -> Vector {
  auto ordered_bits = \
    util::container::convert<std::set>(this->collectUsedBits());

  assert(input.rows() == std::pow(2, ordered_bits.size()));

  auto result = input;
  for(const auto& gate : this->gates_) {
    result = gate->simulate(result, ordered_bits);
  }
  return std::move(result);
}

auto Circuit::simulate(const std::map<Bitno, Vector>& input) const -> Vector {
  auto bits = this->collectUsedBits();

  assert(input.size() == bits.size());

  auto input_vector = util::matrix::createVector({1});
  for(const auto& vector : input) {
    assert(bits.count(vector.first));
    input_vector = util::matrix::tensor(input_vector, vector.second);
  }
  return std::move(this->simulate(input_vector));
}

auto Circuit::print(std::ostream& os) const -> void {
  for(const auto& gate : this->gates_) {
    gate->print(os);
  }
}
}
