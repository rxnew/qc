/**
 * @file general.hpp
 * @brief header of general algorithm
 */

#pragma once

#include "../forward_declarations.hpp"
#include "../gate/gates_wrapper/gates_wrapper_shell.hpp"

namespace qc {
inline namespace algorithm {
inline namespace general {
auto get_cbit(Gate const& gate) -> CBit const&;
auto get_tbit(Gate const& gate) -> TBit const&;
template <class T>
auto add_gate_front(GatesWrapperShell& target, T&& gate) -> void;
template <class T>
auto add_gate_back(GatesWrapperShell& target, T&& gate) -> void;
template <class T>
auto insert_gate_before(GatesWrapperShell& target, GatesCIter pos, T&& gate)
  -> GatesIter;
template <class T>
auto insert_gate_after(GatesWrapperShell& target, GatesCIter pos, T&& gate)
  -> GatesIter;
auto is_cnot(Gate const& gate, bool allow_mtc = false) -> bool;
auto is_overlapped(Gate const& lhs, Gate const& rhs) -> bool;
auto is_overlapped_control(Gate const& lhs, Gate const& rhs) -> bool;
auto is_overlapped_target(Gate const& lhs, Gate const& rhs) -> bool;
auto is_dependent(Gate const& lhs, Gate const& rhs) -> bool;
auto find_min_bit(Gate const& gate) -> BitNo;
auto find_min_bit(Circuit const& circuit) -> BitNo;
template <int dim, class Real>
auto find_min_bit(Gate const& gate,
                  Layout<dim, Real> const& layout) -> BitNo;
template <int dim, class Real>
auto find_min_bit(Circuit const& circuit,
                  Layout<dim, Real> const& layout) -> BitNo;
auto find_max_bit(Gate const& gate) -> BitNo;
auto find_max_bit(Circuit const& circuit) -> BitNo;
template <int dim, class Real>
auto find_max_bit(Gate const& gate,
                  Layout<dim, Real> const& layout) -> BitNo;
template <int dim, class Real>
auto find_max_bit(Circuit const& circuit,
                  Layout<dim, Real> const& layout) -> BitNo;
auto decomp_to_single_target_gates(Gate const& gate) -> Gates;
auto decomp_to_single_target_gates(Circuit const& circuit) -> Circuit;
}
}
}

#include "general/general_impl.hpp"
