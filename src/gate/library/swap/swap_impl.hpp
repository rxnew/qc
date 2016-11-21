#pragma once

namespace qc {
template <class... Args>
SwapCore::SwapCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto SwapCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
