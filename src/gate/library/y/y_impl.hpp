#pragma once

namespace qc {
template <class... Args>
YKernel::YKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto YKernel::is_dagger() const -> bool {
  return false;
}

inline auto YKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto YKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
