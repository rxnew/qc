/**
 * @file gate_dependency.hpp
 * @brief header of GateDependency class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
struct GateDependency {
  auto operator()(std::shared_ptr<Gate> const& lhs,
                  std::shared_ptr<Gate> const& rhs) const -> bool;
};
}
}
}

#include "gate_dependency/gate_dependency_impl.hpp"
