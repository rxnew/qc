#pragma once

namespace qc {
template <class... Args>
VKernel::VKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto VKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

template <class... Args>
VDaggerKernel::VDaggerKernel(Args&&... args)
  : GateKernel(std::forward<Args>(args)...) {}

inline auto VDaggerKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
