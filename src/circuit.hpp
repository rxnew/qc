/**
 * @file circuit.hpp
 * @brief header of Circuit class
 */

#pragma once

#include <list>

#include "gate.hpp"
#include "util/tmpl.hpp"

namespace qc {
using Gates = std::list<Gate>;
using GatesIter = Gates::iterator;
using GatesCIter = Gates::const_iterator;

/**
 * @brief quantum circuit class
 */
class Circuit {
 public:
  Circuit() = default;
  template <class StringT>
  explicit Circuit(StringT&& description);
  template <class StringT>
  Circuit(Gates&& gates, StringT&& description = "");
  template <class GatesT, class stringT,
            util::tmpl::enable_if_lvalue_t<GatesT>* = nullptr>
  Circuit(GatesT&& gates, stringT&& description = "");
  template <class GatesT, class stringT,
            util::tmpl::enable_if_rvalue_t<GatesT>* = nullptr>
  Circuit(GatesT&& gates, stringT&& description = "");
  Circuit(Circuit const& other) = default;
  Circuit(Circuit&&) noexcept = default;

  ~Circuit() noexcept = default;

  auto operator=(Circuit const& other) -> Circuit& = default;
  auto operator=(Circuit&&) noexcept -> Circuit& = default;
  auto operator==(Circuit const& other) const -> bool;
  auto operator!=(Circuit const& other) const -> bool;

  [[deprecated("please use get_gates()")]]
  auto _get_gates() -> Gates&;
  auto get_gates() const -> Gates const&;
  auto set_gates(Gates&& gates) -> void;
  template <class GatesT, util::tmpl::enable_if_lvalue_t<GatesT>* = nullptr>
  auto set_gates(GatesT&& gates) -> void;
  template <class GatesT, util::tmpl::enable_if_rvalue_t<GatesT>* = nullptr>
  auto set_gates(GatesT&& gates) -> void;
  auto get_description() const -> std::string const&;
  template <class StringT>
  auto set_description(StringT&& description) -> void;
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
  auto extend(Circuit const& circuit) -> Circuit&;
  auto extend(Circuit&& circuit) -> Circuit&;
  auto clear() -> void;
  auto get_gates_count() const -> size_t;
  auto collect_bits() const -> BitNos;
  auto print(std::ostream& os = std::cout) const -> void;

 private:
  Gates gates_;
  std::string description_;
};
}

#include "circuit/circuit_impl.hpp"
