#pragma once

namespace qc {
template <class... Args>
SwapKernel::SwapKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto SwapKernel::is_dagger() const -> bool {
  return false;
}

inline auto SwapKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto SwapKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
