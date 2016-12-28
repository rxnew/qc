#pragma once

#include "../../general.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
inline auto GateOverlapped::operator()(Gate const& lhs, Gate const& rhs) const
  -> bool {
  return is_overlapped(lhs, rhs);
}

inline auto GateDependency::operator()(std::shared_ptr<Gate> const& lhs,
                                       std::shared_ptr<Gate> const& rhs) const
  -> bool {
  return is_dependent(*lhs, *rhs);
}
}
}
}
