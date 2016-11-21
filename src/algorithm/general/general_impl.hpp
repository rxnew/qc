/**
 * @file general_impl.hpp
 * @brief implementation header general algorithm
 */

#pragma once

#include "../../debug/assert.hpp"

namespace qc {
template <class T>
auto add_gate_front(GatesWrapperShell& target, T&& gate) -> void {
  target.insert_gate(target.cbegin_gates(), std::forward<T>(gate));
}

template <class T>
auto add_gate_back(GatesWrapperShell& target, T&& gate) -> void {
  target.add_gate(std::forward<T>(gate));
}

template <class T>
auto insert_gate_before(GatesWrapperShell& target, GatesCIter pos, T&& gate)
  -> GatesIter {
  return target.insert_gate(pos, std::forward<T>(gate));
}

template <class T>
auto insert_gate_after(GatesWrapperShell& target, GatesCIter pos, T&& gate)
  -> GatesIter {
  assert_m(pos != target.cend_gates(),
           "Cannot insert a gate after the end of a iterator.");
  return target.insert_gate(++pos, std::forward<T>(gate));
}
}
