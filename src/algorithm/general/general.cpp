/**
 * @file general.cpp
 * @brief implementation of general algorithm
 */

#include "../general.hpp"
#include "general_private.hpp"

#include "../../gate/library.hpp"
#include "../../gate/group.hpp"
#include "../../circuit.hpp"

namespace qc {
inline namespace algorithm {
inline namespace general {
auto get_cbit(Gate const& gate) -> CBit const& {
  assert(gate.is_single_controlled());
  return *gate.get_cbits().cbegin();
}

auto get_tbit(Gate const& gate) -> TBit const& {
  assert(gate.is_single_target());
  return *gate.get_tbits().cbegin();
}

auto is_cnot(Gate const& gate, bool allow_mtc) -> bool {
  return
    gate.get_type() == GateType::X &&
    gate.is_single_controlled() &&
    (allow_mtc || gate.is_single_target());
}

auto is_overlapped(Gate const& lhs, Gate const& rhs) -> bool {
  for(auto const& cbit : lhs.get_cbits()) {
    if(rhs.has_cbit(cbit.get_no())) return true;
    if(rhs.has_tbit(cbit.get_no())) return true;
  }
  for(auto const& tbit : lhs.get_tbits()) {
    if(rhs.has_cbit(tbit.get_no())) return true;
    if(rhs.has_tbit(tbit.get_no())) return true;
  }
  return false;
}

auto is_overlapped_control(Gate const& lhs, Gate const& rhs) -> bool {
  for(auto const& cbit : lhs.get_cbits()) {
    if(rhs.has_cbit(cbit.get_no())) return true;
  }
  return false;
}

auto is_overlapped_target(Gate const& lhs, Gate const& rhs) -> bool {
  for(auto const& tbit : lhs.get_tbits()) {
    if(rhs.has_tbit(tbit.get_no())) return true;
  }
  return false;
}

// Xゲートのみ実装
auto is_dependent(Gate const& lhs, Gate const& rhs) -> bool {
  if(lhs.get_type() == GateType::X && lhs.get_type() == GateType::X) {
    for(auto const& cbit : lhs.get_cbits()) {
      if(rhs.has_tbit(cbit.get_no())) return true;
    }
    for(auto const& cbit : rhs.get_cbits()) {
      if(lhs.has_tbit(cbit.get_no())) return true;
    }
    return false;
  }
  return is_overlapped(lhs, rhs);
}

auto decomp_to_single_target_gates(Gate const& gate) -> Gates {
  if(gate.is_group()) return _decomp_to_single_target_gates(gate);

  auto const& gate_type_name = gate.get_type_name();
  auto const& cbits = gate.get_cbits();
  auto const& tbits = gate.get_tbits();
  auto gates = Gates();
  for(auto const& tbit : tbits) {
    gates.push_back(make_gate(gate_type_name, cbits, tbit));
  }
  return gates;
}

auto decomp_to_single_target_gates(Circuit const& circuit) -> Circuit {
  return Circuit(_decomp_to_single_target_gates(circuit));
}

auto _decomp_to_single_target_gates(GatesWrapperShell const& target) -> Gates {
  auto result_gates = Gates();
  auto const& gates = target.get_gates();
  for(auto const& gate : gates) {
    auto single_target_gates = decomp_to_single_target_gates(gate);
    if(gate.is_group()) {
      result_gates.push_back(Group::make(std::move(single_target_gates)));
    }
    else {
      result_gates.splice(result_gates.cend(), std::move(single_target_gates));
    }
  }
  return result_gates;
}
}
}
}
