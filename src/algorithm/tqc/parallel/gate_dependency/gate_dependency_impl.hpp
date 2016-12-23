#pragma once

#include "../../../general.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
inline auto GateDependency::operator()(std::shared_ptr<Gate> const& lhs,
                                       std::shared_ptr<Gate> const& rhs) const
  -> bool {
  return is_dependent(*lhs, *rhs);
}
}
}
}
