#pragma once

#include <iostream>

#include "../../forward_declarations.hpp"
#include "../../util/tmpl.hpp"

namespace qc {
class GatesWrapperShell {
 public:
  GatesWrapperShell() = default;

  virtual ~GatesWrapperShell() noexcept = default;

  virtual auto get_gates() const -> Gates const& = 0;
  auto set_gates(Gates&& gates) -> void;
  template <class GatesT, util::tmpl::enable_if_lvalue_t<GatesT>* = nullptr>
  auto set_gates(GatesT&& gates) -> void;
  template <class GatesT, util::tmpl::enable_if_rvalue_t<GatesT>* = nullptr>
  auto set_gates(GatesT&& gates) -> void;
  template <class GateT,
            util::tmpl::enable_if_same_plain_t<GateT, Gate>* = nullptr>
  auto add_gate(GateT&& gate) -> void;
  template <class GatesT, util::tmpl::enable_if_container_t<GatesT>* = nullptr>
  auto add_gate(GatesT&& gates) -> void;
  template <class GateT,
            util::tmpl::enable_if_same_plain_t<GateT, Gate>* = nullptr>
  auto insert_gate(GatesCIter pos, GateT&& gate) -> GatesIter;
  template <class GatesT,
            util::tmpl::enable_if_container_t<GatesT>* = nullptr,
            util::tmpl::enable_if_lvalue_t<GatesT>* = nullptr>
  auto insert_gate(GatesCIter pos, GatesT&& gates) -> GatesIter;
  template <class GatesT,
            util::tmpl::enable_if_container_t<GatesT>* = nullptr,
            util::tmpl::enable_if_rvalue_t<GatesT>* = nullptr>
  auto insert_gate(GatesCIter pos, GatesT&& gates) -> GatesIter;
  auto erase_gate(GatesCIter pos) -> GatesIter;
  auto erase_gate(GatesIter pos, Gate& gate) -> GatesIter;
  auto erase_gate(GatesCIter first, GatesCIter last) -> GatesIter;
  auto move_gate(GatesCIter to, GatesIter from) -> GatesIter;
  auto swap_gate(GatesIter pos_a, GatesIter pos_b) -> void;
  auto begin_gates() -> GatesIter;
  auto end_gates() -> GatesIter;
  auto extend(GatesWrapperShell const& circuit) -> GatesWrapperShell&;
  auto extend(GatesWrapperShell&& circuit) -> GatesWrapperShell&;
  auto clear() -> void;
  auto get_gates_count() const -> size_t;
  auto collect_bits() const -> BitNos;
  virtual auto print(std::ostream& os = std::cout) const -> void;
  [[deprecated("please use get_gates()")]]
  auto _get_gates() -> Gates&;

 protected:
    virtual auto get_gates() -> Gates& = 0;
};
}

#include "gates_wrapper_shell/gates_wrapper_shell_impl.hpp"
