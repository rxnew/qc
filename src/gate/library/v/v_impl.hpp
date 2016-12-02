#pragma once

namespace qc {
template <class... Args>
VKernel::VKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto VKernel::get_type() const -> GateType {
  return TYPE;
}
}
