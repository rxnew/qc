#pragma once

namespace qc {
template <class... Args>
inline GroupCore::GroupCore(Args&&... args)
  : GatesWrapperCore(std::forward<Args>(args)...) {}

inline auto GroupCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<GroupCore>(*this);
}

inline auto GroupCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

inline auto GroupCore::get_gates() const -> Gates const& {
  return gates_;
}

inline auto GroupCore::get_gates() -> Gates& {
  return gates_;
}

inline auto GroupCore::get_cbits() -> CBits& {
  return _get_cbits();
}

inline auto GroupCore::get_cbits() const -> CBits const& {
  return _get_cbits();
}

inline auto GroupCore::get_tbits() -> TBits& {
  return _get_tbits();
}

inline auto GroupCore::get_tbits() const -> TBits const& {
  return _get_tbits();
}

template <class... Args>
inline GateType<GroupCore>::GateType(Args&&... args)
  : Gate(new GroupCore(std::forward<Args>(args)...)) {}

inline GateType<GroupCore>::GateType(GateType const& other)
  : Gate(other.core_->clone()) {}

template <class GateCoreU>
inline GateType<GroupCore>::GateType(GateType<GateCoreU> const& gate)
  : Gate(gate.core_->clone()) {}

template <class GateCoreU>
inline GateType<GroupCore>::GateType(GateType<GateCoreU>&& gate)
  : Gate(std::move(gate.core_)) {}

template <class GateCoreU>
inline auto GateType<GroupCore>::operator=(GateType<GateCoreU> const& gate)
  -> GateType& {
  core_ = gate.core_->clone();
  return *this;
}

template <class GateCoreU>
inline auto GateType<GroupCore>::operator=(GateType<GateCoreU>&& gate)
  -> GateType& {
  core_ = std::move(gate.core_);
  return *this;
}

template <class... Args>
inline auto GateType<GroupCore>::make(Args&&... args) -> Gate {
  return Gate::make<GateType<GroupCore>>(std::forward<Args>(args)...);
}

inline auto GateType<GroupCore>::is_group(Gate const& target) -> bool {
  return ALIASES == target.get_type_name();
}
}
