#pragma once

namespace qc {
template <class GateKernelT>
inline Unit<GateKernelT>::Unit() : Gate(new GateKernelT()) {}

template <class GateKernelT>
template <class... Args, class>
inline Unit<GateKernelT>::Unit(Args&&... args)
  : Gate(new GateKernelT(std::forward<Args>(args)...)) {}

template <class GateKernelT>
inline Unit<GateKernelT>::Unit(Unit const& other)
  : Gate(other.kernel_->clone()) {}

template <class GateKernelT>
inline auto Unit<GateKernelT>::operator=(Unit const& gate)
  -> Unit& {
  kernel_ = gate.kernel_->clone();
  return *this;
}
}
