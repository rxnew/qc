#pragma once

namespace qc {
template <class... Args>
ZKernel::ZKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto ZKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
