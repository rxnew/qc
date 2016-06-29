/**
 * @file oracle_impl.hpp
 * @brief implementation header of algorithm for quantum oracle
 */

#pragma once

#include "../../gate/library/x.hpp"

namespace qc {
template <class GatePtrT>
auto getMctCost(const GatePtrT& gate) -> int {
  assert(gate->getTypeName() == X::TYPE_NAME);

  // Please refer to arXiv:quant-ph/0403053
  static constexpr std::array<int, 11> COSTS = {
    1, 1, 5, 13, 29, 61, 52, 125, 253, 509, 1021
  };

  auto size = gate->getCbitList().size();
  auto n = gate->getTbitList().size();
  return (size < COSTS.size() ? COSTS[size] : std::pow(2, size) - 3) * n;
}
}
