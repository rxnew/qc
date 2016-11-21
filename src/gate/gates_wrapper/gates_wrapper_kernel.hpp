#pragma once

#include "../../forward_declarations.hpp"
#include "../../gate.hpp"
#include "../../util/tmpl.hpp"

namespace qc {
class GatesWrapperKernel {
 public:
  GatesWrapperKernel() = default;
  template <class GateT,
            util::tmpl::enable_if_convertible_t<GateT, Gate>* = nullptr>
  GatesWrapperKernel(GateT&& gate);
  GatesWrapperKernel(Gates&& gates);
  template <class GatesT,
            util::tmpl::enable_if_container_t<GatesT>* = nullptr,
            util::tmpl::enable_if_lvalue_t<GatesT>* = nullptr>
  GatesWrapperKernel(GatesT&& gates);
  template <class GatesT,
            util::tmpl::enable_if_container_t<GatesT>* = nullptr,
            util::tmpl::enable_if_rvalue_t<GatesT>* = nullptr>
  GatesWrapperKernel(GatesT&& gates);
  GatesWrapperKernel(GatesWrapperKernel const& other) = default;
  GatesWrapperKernel(GatesWrapperKernel&&) noexcept = default;

  virtual ~GatesWrapperKernel() noexcept = default;

  auto operator=(GatesWrapperKernel const& other)
    -> GatesWrapperKernel& = default;
  auto operator=(GatesWrapperKernel&&) noexcept
    -> GatesWrapperKernel& = default;
  auto operator==(GatesWrapperKernel const& other) const -> bool;
  auto operator!=(GatesWrapperKernel const& other) const -> bool;

 protected:
  Gates gates_;
};
}

#include "gates_wrapper_kernel/gates_wrapper_kernel_impl.hpp"
