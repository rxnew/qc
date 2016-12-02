/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "../gate.hpp"

namespace qc {
auto Gate::operator!() const & -> Gate {
  auto gate = *this;
  gate.kernel_->invert();
  return gate;
}

auto Gate::operator!() && -> Gate {
  kernel_->invert();
  return std::move(*this);
}

auto Gate::get_type() const -> GateType {
  return kernel_->get_type();
}
}
