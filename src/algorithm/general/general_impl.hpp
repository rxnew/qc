/**
 * @file general_impl.hpp
 * @brief implementation header general algorithm
 */

#pragma once

#include "../../layout.hpp"
#include "../../debug/assert.hpp"

namespace qc {
inline namespace algorithm {
inline namespace general {
// prototype declarations
template <class T>
auto _find_min_bit(T const& target) -> BitNo;
template <class T, int dim, class Real>
auto _find_min_bit(T const& target,
                   Layout<dim, Real> const& layout) -> BitNo;
template <class T>
auto _find_max_bit(T const& target) -> BitNo;
template <class T, int dim, class Real>
auto _find_max_bit(T const& target,
                   Layout<dim, Real> const& layout) -> BitNo;

// implementations
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

inline auto find_min_bit(Gate const& gate) -> BitNo {
  return _find_min_bit(gate);
}

inline auto find_min_bit(Circuit const& circuit) -> BitNo {
  return _find_min_bit(circuit);
}

template <int dim, class Real>
inline auto find_min_bit(Gate const& gate,
                         Layout<dim, Real> const& layout) -> BitNo {
  return _find_min_bit(gate, layout);
}

template <int dim, class Real>
inline auto find_min_bit(Circuit const& circuit,
                         Layout<dim, Real> const& layout) -> BitNo {
  return _find_min_bit(circuit, layout);
}

inline auto find_max_bit(Gate const& gate) -> BitNo {
  return _find_max_bit(gate);
}

inline auto find_max_bit(Circuit const& circuit) -> BitNo {
  return _find_max_bit(circuit);
}

template <int dim, class Real>
inline auto find_max_bit(Gate const& gate,
                         Layout<dim, Real> const& layout) -> BitNo {
  return _find_max_bit(gate, layout);
}

template <int dim, class Real>
inline auto find_max_bit(Circuit const& circuit,
                         Layout<dim, Real> const& layout) -> BitNo {
  return _find_max_bit(circuit, layout);
}

template <class T>
auto _find_min_bit(T const& target) -> BitNo {
  auto min_bit = std::numeric_limits<unsigned int>::max();
  for(auto const& bit : target.collect_bits()) {
    min_bit = std::min(min_bit, bit);
  }
  return min_bit;
}

template <class T, int dim, class Real>
auto _find_min_bit(T const& target,
                   Layout<dim, Real> const& layout) -> BitNo {
  auto min_bit = std::numeric_limits<unsigned int>::max();
  for(auto const& bit : target.collect_bits()) {
    if(layout[bit] < layout[min_bit]) min_bit = bit;
  }
  return min_bit;
}

template <class T>
auto _find_max_bit(T const& target) -> BitNo {
  auto max_bit = 0_bit;
  for(auto const& bit : target.collect_bits()) {
    max_bit = std::max(max_bit, bit);
  }
  return max_bit;
}

template <class T, int dim, class Real>
auto _find_max_bit(T const& target,
                   Layout<dim, Real> const& layout) -> BitNo {
  auto max_bit = 0_bit;
  for(auto const& bit : target.collect_bits()) {
    if(layout[bit] > layout[max_bit]) max_bit = bit;
  }
  return max_bit;
}
}
}
}
