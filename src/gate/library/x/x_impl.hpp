#pragma once

namespace qc {
template <class... Args>
XCore::XCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto XCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
