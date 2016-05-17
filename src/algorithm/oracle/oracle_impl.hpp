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
  static const std::vector<int> mct_costs = {
    1, 1, 5, 13, 29, 61, 52, 125, 253, 509, 1021
  };

  auto size = gate->getCbitList().size();
  return size < mct_costs.size() ? mct_costs[size] : std::pow(2, size) - 3;
}
}
