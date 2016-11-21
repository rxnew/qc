#pragma once

namespace qc {
template <class... Args>
WCore::WCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto WCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

template <class... Args>
WDaggerCore::WDaggerCore(Args&&... args)
  : GateCore(std::forward<Args>(args)...) {}

inline auto WDaggerCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
