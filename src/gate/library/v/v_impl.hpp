#pragma once

namespace qc {
template <class... Args>
VCore::VCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto VCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

template <class... Args>
VDaggerCore::VDaggerCore(Args&&... args)
  : GateCore(std::forward<Args>(args)...) {}

inline auto VDaggerCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
