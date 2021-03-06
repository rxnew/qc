#pragma once

namespace qc {
inline Unit<GroupKernel>::Unit() : Gate(new GroupKernel()) {}

template <class... Args, class>
inline Unit<GroupKernel>::Unit(Args&&... args)
  : Gate(new GroupKernel(std::forward<Args>(args)...)) {}

inline Unit<GroupKernel>::Unit(Unit const& other)
  : Gate(other.kernel_->clone()) {}

template <class... Args>
inline auto Unit<GroupKernel>::make(Args&&... args) -> Gate {
  return Gate::make<Unit<GroupKernel>>(std::forward<Args>(args)...);
}

inline auto Unit<GroupKernel>::operator=(Unit const& gate)
  -> Unit& {
  kernel_ = gate.kernel_->clone();
  return *this;
}

template <class... Args>
inline auto make_group(Args&&... args) -> Gate {
  return Group::make(std::forward<Args>(args)...);
}
}
