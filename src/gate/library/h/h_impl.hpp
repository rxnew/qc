#pragma once

namespace qc {
template <class... Args>
HCore::HCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto HCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
