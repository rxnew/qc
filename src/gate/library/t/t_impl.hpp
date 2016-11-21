#pragma once

namespace qc {
template <class... Args>
TCore::TCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto TCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

template <class... Args>
TDaggerCore::TDaggerCore(Args&&... args)
  : GateCore(std::forward<Args>(args)...) {}

inline auto TDaggerCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
