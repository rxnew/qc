#pragma once

namespace qc {
template <class... Args>
XKernel::XKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto XKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
