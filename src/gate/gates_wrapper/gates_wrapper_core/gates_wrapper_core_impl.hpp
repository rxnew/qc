#pragma once

namespace qc {
template <class GateT, util::tmpl::enable_if_convertible_t<GateT, Gate>*>
inline GatesWrapperCore::GatesWrapperCore(GateT&& gate)
  : gates_{std::forward<GateT>(gate)} {}

inline GatesWrapperCore::GatesWrapperCore(Gates&& gates)
  : gates_(std::move(gates)) {}

template <class GatesT,
          util::tmpl::enable_if_container_t<GatesT>*,
          util::tmpl::enable_if_lvalue_t<GatesT>*>
inline GatesWrapperCore::GatesWrapperCore(GatesT&& gates)
  : gates_(std::cbegin(gates), std::cend(gates)) {}

template <class GatesT,
          util::tmpl::enable_if_container_t<GatesT>*,
          util::tmpl::enable_if_rvalue_t<GatesT>*>
inline GatesWrapperCore::GatesWrapperCore(GatesT&& gates)
  : gates_(std::make_move_iterator(std::begin(gates)),
           std::make_move_iterator(std::end(gates))) {}

inline auto GatesWrapperCore::operator==(GatesWrapperCore const& other) const
  -> bool {
  return gates_ == other.gates_;
}

inline auto GatesWrapperCore::operator!=(GatesWrapperCore const& other) const
  -> bool {
  return !(*this == other);
}
}
