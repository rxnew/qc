#pragma once

namespace qc {
template <class... Args>
SKernel::SKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto SKernel::get_type() const -> GateType {
  return TYPE;
}
}
