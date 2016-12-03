#pragma once

namespace qc {
template <class... Args>
HKernel::HKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto HKernel::bedaggered() const -> bool {
  return false;
}

inline auto HKernel::invert() -> void {}

inline auto HKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto HKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
