#pragma once

namespace qc {
template <class... Args>
SKernel::SKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto SKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}

template <class... Args>
SDaggerKernel::SDaggerKernel(Args&&... args)
  : UnitKernel(std::forward<Args>(args)...) {}

inline auto SDaggerKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}
}
