#pragma once

namespace qc {
template <class... Args>
IKernel::IKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto IKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}
}
