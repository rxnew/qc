#pragma once

namespace qc {
template <class... Args>
ZKernel::ZKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto ZKernel::bedaggered() const -> bool {
  return false;
}

inline auto ZKernel::invert() -> void {}

inline auto ZKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto ZKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
