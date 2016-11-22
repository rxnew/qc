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
inline auto GateType<GateKernelT>::operator=(GateType const& gate)
  -> GateType& {
  kernel_ = gate.kernel_->clone();
  return *this;
}
}
