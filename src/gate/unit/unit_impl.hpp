#pragma once

namespace qc {
template <class GateKernelT>
inline Unit<GateKernelT>::Unit() : Gate(new GateKernelT()) {}

template <class GateKernelT>
inline Unit<GateKernelT>::Unit(std::initializer_list<CBit> cbits,
                               std::initializer_list<TBit> tbits)
  : Gate(new GateKernelT(cbits, tbits)) {}

template <class GateKernelT>
inline Unit<GateKernelT>::Unit(bool bedaggered,
                               std::initializer_list<CBit> cbits,
                               std::initializer_list<TBit> tbits)
  : Gate(new GateKernelT(bedaggered, cbits, tbits)) {}

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
