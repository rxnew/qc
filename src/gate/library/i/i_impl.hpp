#pragma once

namespace qc {
template <class... Args>
IKernel::IKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto IKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto IKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
