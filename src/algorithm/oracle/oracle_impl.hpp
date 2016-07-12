/**
 * @file oracle_impl.hpp
 * @brief implementation header of algorithm for quantum oracle
 */

#pragma once

#include "../../gate/library/x.hpp"
#include "../../util/math.hpp"

namespace qc {
template <class GatePtrT>
inline auto collectCbits(const GatePtrT& gate) -> BitList {
  return std::move(qc::collectCbits(*gate));
}

template <class GatePtrT>
inline auto collectTbits(const GatePtrT& gate) -> BitList {
  return std::move(qc::collectTbits(*gate));
}

template <class GatePtrT>
inline auto getMctCost(const GatePtrT& gate) -> unsigned long long {
  return std::move(qc::getMctCost(*gate));
}
}
