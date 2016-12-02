#pragma once

namespace qc {
template <class... Args>
TKernel::TKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto TKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto TKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}

template <class... Args>
TDaggerKernel::TDaggerKernel(Args&&... args)
  : UnitKernel(std::forward<Args>(args)...) {}

inline auto TDaggerKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto TDaggerKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}
}
