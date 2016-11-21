#pragma once

namespace qc {
template <class... Args>
ZCore::ZCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto ZCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
