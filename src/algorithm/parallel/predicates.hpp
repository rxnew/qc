/**
 * @file predicates.hpp
 * @brief header of predicates
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
struct GateOverlapped {
  auto operator()(Gate const& lhs, Gate const& rhs) const -> bool;
};

struct GateDependency {
  auto operator()(std::shared_ptr<Gate> const& lhs,
                  std::shared_ptr<Gate> const& rhs) const -> bool;
};
}
}
}

#include "predicates/predicates_impl.hpp"
