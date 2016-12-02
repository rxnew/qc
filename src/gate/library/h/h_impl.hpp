#pragma once

namespace qc {
template <class... Args>
HKernel::HKernel(Args&&... args) : UnitKernel(std::forward<Args>(args)...) {}

inline auto HKernel::get_type_name() const -> util::string::String const& {
  return TYPE_NAME;
}
}
