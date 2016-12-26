/**
 * @file tqc.hpp
 * @brief header of tqc algorithm
 */

#pragma once

#include "../gate/group.hpp"
#include "../layout.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <int dim, class Real>
auto is_overlapped(Gate const& gate_a, Gate const& gate_b,
                   Layout<dim, Real> const& layout, bool allow_mtc = true)
  -> bool;
template <bool allow_mtc>
struct Overlapped {
  template <int dim, class Real>
  auto operator()(Gate const& gate_a, Gate const& gate_b,
                  Layout<dim, Real> const& layout) const -> bool;
};
}
}
}

#include "tqc/tqc_impl.hpp"
