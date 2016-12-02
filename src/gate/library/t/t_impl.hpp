#pragma once

namespace qc {
template <class... Args>
TKernel::TKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto TKernel::get_type() const -> GateType {
  return TYPE;
}
}
