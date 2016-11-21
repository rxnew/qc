#pragma once

namespace qc {
template <class... Args>
TKernel::TKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto TKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

template <class... Args>
TDaggerKernel::TDaggerKernel(Args&&... args)
  : GateKernel(std::forward<Args>(args)...) {}

inline auto TDaggerKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
