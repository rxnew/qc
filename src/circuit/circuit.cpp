/**
 * @file circuit.cpp
 * @brief implementation of the quantum circuit class
 */

#include "../circuit.hpp"

namespace qc {
auto Circuit::collect_bits() const -> BitNos {
  auto bit_nos = BitNos();
  for(auto const& gate : gates_) {
    auto const gate_bit_nos = gate.collect_bits();
    bit_nos.insert(gate_bit_nos.cbegin(), gate_bit_nos.cend());
  }
  return bit_nos;
}

auto Circuit::print(std::ostream& os) const -> void {
  for(auto const& gate : gates_) {
    gate.print(os);
    os << std::endl;
  }
}
}
