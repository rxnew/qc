#pragma once

namespace qc {
template <class... Args>
YCore::YCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto YCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
