/**
 * @file oracle_impl.hpp
 * @brief implementation header of algorithm for quantum oracle
 */

#pragma once

#include "../../gate/library/x.hpp"
#include "../../util/math.hpp"

namespace qc {
template <class GatePtrT>
auto getMctCost(const GatePtrT& gate) -> unsigned long long {
  assert(gate->getTypeName() == X::TYPE_NAME);

  // Please refer to arXiv:quant-ph/0403053
  static constexpr std::array<unsigned long long, 11> C = {
    1, 1, 5, 13, 29, 61, 52, 125, 253, 509, 1021
  };

  auto size = gate->getCbitList().size();
  auto n = static_cast<unsigned long long>(gate->getTbitList().size());
  return (size < C.size() ? C[size] : util::math::pow(2ull, size) - 3) * n;
}
}
