#pragma once

namespace qc {
template <class... Args>
inline GroupKernel::GroupKernel(Args&&... args)
  : GatesWrapperKernel(std::forward<Args>(args)...) {}

inline auto GroupKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<GroupKernel>(*this);
}

inline auto GroupKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

inline auto GroupKernel::get_cbits() -> CBits& {
  return _get_cbits();
}

inline auto GroupKernel::get_cbits() const -> CBits const& {
  return _get_cbits();
}

inline auto GroupKernel::get_tbits() -> TBits& {
  return _get_tbits();
}

inline auto GroupKernel::get_tbits() const -> TBits const& {
  return _get_tbits();
}

inline auto GroupKernel::get_gates() -> Gates& {
  return gates_;
}

inline auto GroupKernel::get_gates() const -> Gates const& {
  return gates_;
}

template <class... Args>
inline GateType<GroupKernel>::GateType(Args&&... args)
  : Gate(new GroupKernel(std::forward<Args>(args)...)) {}

inline GateType<GroupKernel>::GateType(GateType const& other)
  : Gate(other.kernel_->clone()) {}

template <class GateKernelU>
inline GateType<GroupKernel>::GateType(GateType<GateKernelU> const& gate)
  : Gate(gate.kernel_->clone()) {}

template <class GateKernelU>
inline GateType<GroupKernel>::GateType(GateType<GateKernelU>&& gate)
  : Gate(std::move(gate.kernel_)) {}

template <class GateKernelU>
inline auto GateType<GroupKernel>::operator=(GateType<GateKernelU> const& gate)
  -> GateType& {
  kernel_ = gate.kernel_->clone();
  return *this;
}

template <class GateKernelU>
inline auto GateType<GroupKernel>::operator=(GateType<GateKernelU>&& gate)
  -> GateType& {
  kernel_ = std::move(gate.kernel_);
  return *this;
}

template <class... Args>
inline auto GateType<GroupKernel>::make(Args&&... args) -> Gate {
  return Gate::make<GateType<GroupKernel>>(std::forward<Args>(args)...);
}

inline auto GateType<GroupKernel>::is_group(Gate const& target) -> bool {
  return ALIASES == target.get_type_name();
}
}
