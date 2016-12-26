#pragma once

#include "../general.hpp"
#include "../parallel.hpp"
#include "../../util/vector/point.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <int dim, bool allow_mtc>
auto is_overlapped(Gate const& gate_a, Gate const& gate_b, Layout<dim>& layout)
  -> bool {
  auto cbit_a = get_cbit(gate_a).get_no();
  auto cbit_b = get_cbit(gate_b).get_no();
  auto tbit_a = get_tbit(gate_a).get_no();
  auto tbit_b = get_tbit(gate_b).get_no();
  if(allow_mtc && cbit_a == cbit_b && tbit_a != tbit_b) return false;
  if(is_intersected(layout[cbit_a], layout[tbit_a],
                    layout[cbit_b], layout[tbit_b])) return true;
  return false;
}

template <bool allow_mtc>
template <int dim>
auto Overlapped<allow_mtc>::
operator()(Gate const& gate_a, Gate const& gate_b, Layout<dim>& layout) const
  -> bool {
  return is_overlapped<allow_mtc>(gate_a, gate_b, layout);
}
}
}
}
