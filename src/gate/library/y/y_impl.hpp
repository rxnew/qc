#pragma once

namespace qc {
template <class... Args>
YKernel::YKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto YKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
