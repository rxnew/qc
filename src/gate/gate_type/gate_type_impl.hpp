#pragma once

namespace qc {
template <class GateKernelT>
template <class... Args>
inline GateType<GateKernelT>::GateType(Args&&... args)
  : Gate(new GateKernelT(std::forward<Args>(args)...)) {}

template <class GateKernelT>
inline GateType<GateKernelT>::GateType(GateType const& other)
  : Gate(other.kernel_->clone()) {}

template <class GateKernelT>
template <class GateKernelU>
inline GateType<GateKernelT>::GateType(GateType<GateKernelU> const& gate)
  : Gate(gate.kernel_->clone()) {}

template <class GateKernelT>
template <class GateKernelU>
inline GateType<GateKernelT>::GateType(GateType<GateKernelU>&& gate)
  : Gate(std::move(gate.kernel_)) {}

template <class GateKernelT>
template <class GateKernelU>
inline auto GateType<GateKernelT>::operator=(GateType<GateKernelU> const& gate)
  -> GateType& {
  kernel_ = gate.kernel_->clone();
  return *this;
}

template <class GateKernelT>
template <class GateKernelU>
inline auto GateType<GateKernelT>::operator=(GateType<GateKernelU>&& gate)
  -> GateType& {
  kernel_ = std::move(gate.kernel_);
  return *this;
}
}
