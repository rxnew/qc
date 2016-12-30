/**
 * @file tqc.hpp
 * @brief header of tqc algorithm
 */

#pragma once

#include "parallel/engines/csvd_ev1.hpp"
#include "../gate/group.hpp"
#include "../layout.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <template <class...> class Engine = CsvdEv1, bool allow_mtc,
          int dim, class Real>
auto tqc_parallelize(Circuit const& circuit, Layout<dim, Real> const& layout)
  -> Circuit;
template <template <class...> class Engine = CsvdEv1, int dim, class Real>
auto tqc_parallelize(Circuit const& circuit, Layout<dim, Real> const& layout)
  -> Circuit;
template <int dim, class Real>
auto is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                       Layout<dim, Real> const& layout, bool allow_mtc = true)
  -> bool;
template <class Real>
auto is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                       Layout<1, Real> const& layout, bool allow_mtc = true)
  -> bool;
template <int dim, class Real>
auto is_tqc_overlapped_braiding(Gate const& gate_a, Gate const& gate_b,
                                Layout<dim, Real> const& layout,
                                bool allow_mtc = true) -> bool;
template <class Real>
auto is_tqc_overlapped_braiding(Gate const& gate_a, Gate const& gate_b,
                                Layout<1, Real> const& layout,
                                bool allow_mtc = true) -> bool;
template <int dim, class Real>
auto is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                 Layout<dim, Real> const& layout) -> bool;
template <class Real>
auto is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                 Layout<1, Real> const& layout) -> bool;
}
}
}

#include "tqc/tqc_impl.hpp"
