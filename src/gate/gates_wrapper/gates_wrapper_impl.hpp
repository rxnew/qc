#pragma once

namespace qc {
template <class... Args>
inline GatesWrapper::GatesWrapper(Args&&... args)
  : GatesWrapperCore(std::forward<Args>(args)...) {}

inline auto GatesWrapper::get_gates() const -> Gates const& {
  return gates_;
}

inline auto GatesWrapper::get_gates() -> Gates& {
  return gates_;
}
}
