#pragma once

namespace qc {
template <class GateCoreT>
template <class... Args>
inline GateType<GateCoreT>::GateType(Args&&... args)
  : Gate(new GateCoreT(std::forward<Args>(args)...)) {}

template <class GateCoreT>
inline GateType<GateCoreT>::GateType(GateType const& other)
  : Gate(other.core_->clone()) {}

template <class GateCoreT>
template <class GateT>
inline GateType<GateCoreT>::GateType(GateType<GateT> const& gate)
  : Gate(gate.core_->clone()) {}

template <class GateCoreT>
template <class GateT>
inline GateType<GateCoreT>::GateType(GateType<GateT>&& gate)
  : Gate(std::move(gate.core_)) {}

template <class GateCoreT>
template <class GateT>
inline auto GateType<GateCoreT>::operator=(GateType<GateT> const& gate)
  -> GateType& {
  core_ = gate.core_->clone();
  return *this;
}

template <class GateCoreT>
template <class GateT>
inline auto GateType<GateCoreT>::operator=(GateType<GateT>&& gate)
  -> GateType& {
  core_ = std::move(gate.core_);
  return *this;
}
}
