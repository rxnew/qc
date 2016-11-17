/**
 * @file general.cpp
 * @brief implementation of general algorithm
 */

#include "../general.hpp"

#include "../../gate/library.hpp"
#include "../../circuit.hpp"

namespace qc {
auto get_cbit(Gate const& gate) -> CBit const& {
  assert(gate.is_single_controlled());
  return *gate.get_cbits().cbegin();
}

auto get_tbit(Gate const& gate) -> TBit const& {
  assert(gate.is_single_target());
  return *gate.get_tbits().cbegin();
}

auto decomp_to_single_target_gates(Gate const& gate) -> Gates {
  auto const& gate_type_name = gate.get_type_name();
  auto const& cbits = gate.get_cbits();
  auto const& tbits = gate.get_tbits();
  auto gates = Gates();
  for(auto const& tbit : tbits) {
    gates.push_back(make_gate(gate_type_name, cbits, tbit));
  }
  return gates;
}

auto decomp_to_single_target_gates(Circuit& circuit) -> void {
  auto circuit_tmp = Circuit();
  auto const& gates = circuit.get_gates();
  for(auto const& gate : gates) {
    circuit_tmp.insert_gate(gates.cend(), decomp_to_single_target_gates(gate));
  }
  circuit = std::move(circuit_tmp);
}
}
