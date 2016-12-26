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
template <int dim, bool allow_mtc = true>
auto is_overlapped(Gate const& gate_a, Gate const& gate_b, Layout<dim>& layout)
  -> bool;

template <bool allow_mtc>
struct Overlapped {
  template <int dim>
  auto operator()(Gate const& gate_a, Gate const& gate_b, Layout<dim>& layout)
    const -> bool;
};
}
}
}

#include "tqc/tqc_impl.hpp"
