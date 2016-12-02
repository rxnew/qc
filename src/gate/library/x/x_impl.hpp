#pragma once

namespace qc {
template <class... Args>
XKernel::XKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto XKernel::is_dagger() const -> bool {
  return false;
}

inline auto XKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto XKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
