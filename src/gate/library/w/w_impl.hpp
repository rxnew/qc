#pragma once

namespace qc {
template <class... Args>
WKernel::WKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto WKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

template <class... Args>
WDaggerKernel::WDaggerKernel(Args&&... args)
  : GateKernel(std::forward<Args>(args)...) {}

inline auto WDaggerKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
