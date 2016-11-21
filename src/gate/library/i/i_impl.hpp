#pragma once

namespace qc {
template <class... Args>
IKernel::IKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto IKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
