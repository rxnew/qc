#pragma once

#include "../../forward_declarations.hpp"
#include "../../gate.hpp"
#include "../../util/tmpl.hpp"

namespace qc {
class GatesWrapperCore {
 public:
  GatesWrapperCore() = default;
  template <class GateT,
            util::tmpl::enable_if_convertible_t<GateT, Gate>* = nullptr>
  GatesWrapperCore(GateT&& gate);
  GatesWrapperCore(Gates&& gates);
  template <class GatesT,
            util::tmpl::enable_if_container_t<GatesT>* = nullptr,
            util::tmpl::enable_if_lvalue_t<GatesT>* = nullptr>
  GatesWrapperCore(GatesT&& gates);
  template <class GatesT,
            util::tmpl::enable_if_container_t<GatesT>* = nullptr,
            util::tmpl::enable_if_rvalue_t<GatesT>* = nullptr>
  GatesWrapperCore(GatesT&& gates);
  GatesWrapperCore(GatesWrapperCore const& other) = default;
  GatesWrapperCore(GatesWrapperCore&&) noexcept = default;

  virtual ~GatesWrapperCore() noexcept = default;

  auto operator=(GatesWrapperCore const& other) -> GatesWrapperCore& = default;
  auto operator=(GatesWrapperCore&&) noexcept -> GatesWrapperCore& = default;
  auto operator==(GatesWrapperCore const& other) const -> bool;
  auto operator!=(GatesWrapperCore const& other) const -> bool;

 protected:
  Gates gates_;
};
}

#include "gates_wrapper_core/gates_wrapper_core_impl.hpp"
