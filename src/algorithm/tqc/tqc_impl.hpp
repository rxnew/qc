#pragma once

#include "../general.hpp"
#include "../parallel.hpp"
#include "../../util/vector.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
// prototype declarations
template <int dim, class Real>
auto _is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                        Layout<dim, Real> const& layout, bool allow_mtc = true)
  -> bool;
template <class Real>
auto _is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                        Layout<1, Real> const& layout, bool allow_mtc = true)
  -> bool;
template <int dim, class Real>
auto _is_tqc_overlapped_cnot(Gate const& gate_a, Gate const& gate_b,
                             Layout<dim, Real> const& layout,
                             bool allow_mtc = true) -> bool;
template <class Real>
auto _is_tqc_overlapped_cnot(Gate const& gate_a, Gate const& gate_b,
                             Layout<1, Real> const& layout,
                             bool allow_mtc = true) -> bool;
template <int dim, class Real>
auto _is_tqc_overlapped_single_target_cnot(Gate const& gate_a,
                                           Gate const& gate_b,
                                           Layout<dim, Real> const& layout,
                                           bool allow_mtc = true) -> bool;
template <int dim, class Real>
auto _is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                  Layout<dim, Real> const& layout) -> bool;
template <class Real>
auto _is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                  Layout<1, Real> const& layout) -> bool;

// implementations
template <template <class...> class Engine, bool allow_mtc, int dim, class Real>
auto tqc_parallelize(Circuit const& circuit, Layout<dim, Real> const& layout)
  -> Circuit {
  using namespace std::placeholders;
  auto overlapped =
    std::bind(is_tqc_overlapped<dim, Real>, _1, _2, layout, allow_mtc);
  return parallelize<Engine<decltype(overlapped)>>(circuit, overlapped);
}

template <template <class...> class Engine, int dim, class Real>
inline auto tqc_parallelize(Circuit const& circuit,
                            Layout<dim, Real> const& layout) -> Circuit {
  return tqc_parallelize<Engine, true>(circuit, layout);
}

template <int dim, class Real>
auto is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                       Layout<dim, Real> const& layout, bool allow_mtc)
  -> bool {
  return _is_tqc_overlapped(gate_a, gate_b, layout, allow_mtc);
}

template <int dim, class Real>
auto is_tqc_overlapped_cnot(Gate const& gate_a, Gate const& gate_b,
                            Layout<dim, Real> const& layout, bool allow_mtc)
  -> bool {
  return _is_tqc_overlapped_cnot(gate_a, gate_b, layout, allow_mtc);
}

template <int dim, class Real>
auto is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                 Layout<dim, Real> const& layout) -> bool {
  return _is_tqc_overlapped_arbitrary(gate_a, gate_b, layout);
}

template <int dim, class Real>
auto _is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                        Layout<dim, Real> const& layout, bool allow_mtc)
  -> bool {
  if(is_cnot(gate_a) && is_cnot(gate_b)) {
    return
      _is_tqc_overlapped_single_target_cnot(gate_a, gate_b, layout, allow_mtc);
  }
  return _is_tqc_overlapped_arbitrary(gate_a, gate_b, layout);
}

template <class Real>
auto _is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                        Layout<1, Real> const& layout, bool allow_mtc)
  -> bool {
  if(is_cnot(gate_a, true) && is_cnot(gate_b, true)) {
    return _is_tqc_overlapped_cnot(gate_a, gate_b, layout, allow_mtc);
  }
  return _is_tqc_overlapped_arbitrary(gate_a, gate_b, layout);
}

template <int dim, class Real>
auto _is_tqc_overlapped_cnot(Gate const& gate_a, Gate const& gate_b,
                             Layout<dim, Real> const& layout,
                             bool allow_mtc) -> bool {
  return
    _is_tqc_overlapped_single_target_cnot(gate_a, gate_b, layout, allow_mtc);
}

template <class Real>
auto _is_tqc_overlapped_cnot(Gate const& gate_a, Gate const& gate_b,
                             Layout<1, Real> const& layout, bool allow_mtc)
  -> bool {
  if(gate_a.is_single_target() && gate_b.is_single_target()) {
    return
      _is_tqc_overlapped_single_target_cnot(gate_a, gate_b, layout, allow_mtc);
  }
  if(allow_mtc) {
    auto cbit_a = get_cbit(gate_a).get_no();
    auto cbit_b = get_cbit(gate_b).get_no();
    if(cbit_a == cbit_b && !is_overlapped_target(gate_a, gate_b)) return false;
  }
  return _is_tqc_overlapped_arbitrary(gate_a, gate_b, layout);
}

template <int dim, class Real>
auto _is_tqc_overlapped_single_target_cnot(Gate const& gate_a,
                                           Gate const& gate_b,
                                           Layout<dim, Real> const& layout,
                                           bool allow_mtc) -> bool {
  auto cbit_a = get_cbit(gate_a).get_no();
  auto cbit_b = get_cbit(gate_b).get_no();
  auto tbit_a = get_tbit(gate_a).get_no();
  auto tbit_b = get_tbit(gate_b).get_no();
  if(allow_mtc && cbit_a == cbit_b && tbit_a != tbit_b) return false;
  return is_intersected(layout[cbit_a], layout[tbit_a],
                        layout[cbit_b], layout[tbit_b]);
}

// 未実装
template <int dim, class Real>
auto _is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                  Layout<dim, Real> const& layout) -> bool {
  return true;
}

template <class Real>
auto _is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                  Layout<1, Real> const& layout) -> bool {
  auto min_bit_a = find_min_bit(gate_a, layout).get_no();
  auto min_bit_b = find_min_bit(gate_b, layout).get_no();
  auto max_bit_a = find_max_bit(gate_a, layout).get_no();
  auto max_bit_b = find_max_bit(gate_b, layout).get_no();
  return is_intersected(layout[min_bit_a], layout[max_bit_a],
                        layout[min_bit_b], layout[max_bit_b]);
}
}
}
}
