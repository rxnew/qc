#pragma once

namespace qc {
template <class... Args>
ZKernel::ZKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto ZKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}
}
