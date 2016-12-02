#pragma once

namespace qc {
template <class... Args>
XKernel::XKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto XKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}
}
