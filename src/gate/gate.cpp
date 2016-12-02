/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "../gate.hpp"

#include "gate_type.hpp"

namespace qc {
auto Gate::get_type() const -> GateType {
  return kernel_->get_type();
}
}
