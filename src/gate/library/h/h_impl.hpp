#pragma once

namespace qc {
template <class... Args>
HKernel::HKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto HKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
