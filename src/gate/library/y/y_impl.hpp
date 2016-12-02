#pragma once

namespace qc {
template <class... Args>
YKernel::YKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto YKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}
}
