/**
 * @file circuit_impl.hpp
 * @brief implementation header of Circuit class
 */

#pragma once

namespace qc {
template <class StringT>
inline Circuit::Circuit(StringT&& description)
  : description_(std::forward<StringT>(description)) {}

template <class StringT>
inline Circuit::Circuit(Gates&& gates, StringT&& description)
  : gates_(std::move(gates)),
    description_(std::forward<StringT>(description)) {}

template <class GatesT, class stringT, util::tmpl::enable_if_lvalue_t<GatesT>*>
inline Circuit::Circuit(GatesT&& gates, stringT&& description)
  : gates_(std::cbegin(gates), std::cend(gates)),
    description_(std::forward<stringT>(description)) {}

template <class GatesT, class stringT, util::tmpl::enable_if_rvalue_t<GatesT>*>
inline Circuit::Circuit(GatesT&& gates, stringT&& description)
  : gates_(std::make_move_iterator(std::begin(gates)),
           std::make_move_iterator(std::end(gates))),
    description_(std::forward<stringT>(description)) {}

inline auto Circuit::operator==(Circuit const& other) const -> bool {
  return gates_ == other.gates_;
}

inline auto Circuit::operator!=(Circuit const& other) const -> bool {
  return !(*this == other);
}

inline auto Circuit::_get_gates() -> Gates& {
  return gates_;
}

inline auto Circuit::get_gates() const -> Gates const& {
  return gates_;
}

inline auto Circuit::set_gates(Gates&& gates) -> void {
  gates_ = std::move(gates);
}

template <class GatesT, util::tmpl::enable_if_lvalue_t<GatesT>*>
inline auto Circuit::set_gates(GatesT&& gates) -> void {
  gates_.assign(std::cbegin(gates), std::cend(gates));
}

template <class GatesT, util::tmpl::enable_if_rvalue_t<GatesT>*>
inline auto Circuit::set_gates(GatesT&& gates) -> void {
  gates_.assign(std::make_move_iterator(std::begin(gates)),
                std::make_move_iterator(std::end(gates)));
}

inline auto Circuit::get_description() const -> std::string const& {
  return description_;
}

template <class StringT>
inline auto Circuit::set_description(StringT&& description) -> void {
  description_ = std::forward<StringT>(description);
}

template <class GateT, util::tmpl::enable_if_same_plain_t<GateT, Gate>*>
inline auto Circuit::add_gate(GateT&& gate) -> void {
  gates_.push_back(std::forward<GateT>(gate));
}

template <class GatesT, util::tmpl::enable_if_container_t<GatesT>*>
inline auto Circuit::add_gate(GatesT&& gates) -> void {
  insert_gate(std::cend(gates_), std::forward<GatesT>(gates));
}

template <class GateT, util::tmpl::enable_if_same_plain_t<GateT, Gate>*>
inline auto Circuit::insert_gate(GatesCIter pos, GateT&& gate) -> GatesIter {
  return gates_.insert(pos, std::forward<GateT>(gate));
}

template <class GatesT,
          util::tmpl::enable_if_container_t<GatesT>*,
          util::tmpl::enable_if_lvalue_t<GatesT>*>
inline auto Circuit::insert_gate(GatesCIter pos, GatesT&& gates) -> GatesIter {
  return gates_.insert(pos, std::cbegin(gates), std::cend(gates));
}

template <class GatesT,
          util::tmpl::enable_if_container_t<GatesT>*,
          util::tmpl::enable_if_rvalue_t<GatesT>*>
inline auto Circuit::insert_gate(GatesCIter pos, GatesT&& gates) -> GatesIter {
  return gates_.insert(pos,
                       std::make_move_iterator(std::begin(gates)),
                       std::make_move_iterator(std::end(gates)));
}

inline auto Circuit::erase_gate(GatesCIter pos) -> GatesIter {
  return gates_.erase(pos);
}

inline auto Circuit::erase_gate(GatesIter pos, Gate& gate) -> GatesIter {
  gate = std::move(*pos);
  return erase_gate(pos);
}

inline auto Circuit::erase_gate(GatesCIter first, GatesCIter last) -> GatesIter {
  return gates_.erase(first, last);
}

inline auto Circuit::move_gate(GatesCIter to, GatesIter from) -> GatesIter {
  insert_gate(to, std::move(*from));
  return erase_gate(from);
}

inline auto Circuit::swap_gate(GatesIter pos_a, GatesIter pos_b) -> void {
  std::swap(*pos_a, *pos_b);
}

inline auto Circuit::begin_gates() -> GatesIter {
  return std::begin(gates_);
}

inline auto Circuit::end_gates() -> GatesIter {
  return std::end(gates_);
}

inline auto Circuit::extend(Circuit const& circuit) -> Circuit& {
  add_gate(circuit.gates_);
  return *this;
}

inline auto Circuit::extend(Circuit&& circuit) -> Circuit& {
  add_gate(std::move(circuit.gates_));
  return *this;
}

inline auto Circuit::clear() -> void {
  gates_.clear();
}

inline auto Circuit::get_gates_count() const -> size_t {
  return gates_.size();
}
}
