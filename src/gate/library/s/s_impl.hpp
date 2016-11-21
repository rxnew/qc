#pragma once

namespace qc {
template <class... Args>
SCore::SCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto SCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

template <class... Args>
SDaggerCore::SDaggerCore(Args&&... args)
  : GateCore(std::forward<Args>(args)...) {}

inline auto SDaggerCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
