#pragma once

namespace qc {
template <class... Args>
ICore::ICore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto ICore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
