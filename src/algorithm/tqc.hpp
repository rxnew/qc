/**
 * @file tqc.hpp
 * @brief header of tqc algorithm
 */

#pragma once

#include "parallel/engines/csvd_ev1.hpp"
#include "../forward_declarations.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <template <class...> class Engine = CsvdEv1, int dim, class Real>
auto tqc_parallelize(Circuit const& circuit, Layout<dim, Real> const& layout,
                     bool allow_mtc = true) -> Circuit;
template <int dim, class Real>
auto is_tqc_overlapped(Gate const& gate_a, Gate const& gate_b,
                       Layout<dim, Real> const& layout, bool allow_mtc = true)
  -> bool;
template <int dim, class Real>
auto is_tqc_overlapped_cnot(Gate const& gate_a, Gate const& gate_b,
                            Layout<dim, Real> const& layout,
                            bool allow_mtc = true) -> bool;
template <int dim, class Real>
auto is_tqc_overlapped_arbitrary(Gate const& gate_a, Gate const& gate_b,
                                 Layout<dim, Real> const& layout) -> bool;
auto combine_cnot_into_mtc(Gate const& gate) -> Gate;
auto combine_cnot_into_mtc(Circuit const& circuit) -> Circuit;
}
}
}

#include "tqc/tqc_impl.hpp"
