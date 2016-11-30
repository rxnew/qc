#pragma once

namespace qc {
template <class... Args>
SwapKernel::SwapKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto SwapKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
