#pragma once

namespace qc {
template <class... Args>
WKernel::WKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto WKernel::get_type() const -> GateType {
  return TYPE;
}
}
