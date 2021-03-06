#pragma once

namespace qc {
template <class... Args>
SwapKernel::SwapKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto SwapKernel::bedaggered() const -> bool {
  return false;
}

inline auto SwapKernel::invert() -> void {}

inline auto SwapKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto SwapKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
