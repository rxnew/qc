#pragma once

namespace qc {
template <class... Args>
WKernel::WKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto WKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}

template <class... Args>
WDaggerKernel::WDaggerKernel(Args&&... args)
  : UnitKernel(std::forward<Args>(args)...) {}

inline auto WDaggerKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}
}
