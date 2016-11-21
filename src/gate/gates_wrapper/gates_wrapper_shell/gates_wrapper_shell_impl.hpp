#pragma once

namespace qc {
template <class GatesT, util::tmpl::enable_if_lvalue_t<GatesT>*>
auto GatesWrapperShell::set_gates(GatesT&& gates) -> void {
  get_gates().assign(std::cbegin(gates), std::cend(gates));
}

template <class GatesT, util::tmpl::enable_if_rvalue_t<GatesT>*>
auto GatesWrapperShell::set_gates(GatesT&& gates) -> void {
  get_gates().assign(std::make_move_iterator(std::begin(gates)),
                     std::make_move_iterator(std::end(gates)));
}

template <class GateT, util::tmpl::enable_if_convertible_t<GateT, Gate>*>
auto GatesWrapperShell::add_gate(GateT&& gate) -> void {
  get_gates().push_back(std::forward<GateT>(gate));
}

template <class GatesT, util::tmpl::enable_if_container_t<GatesT>*>
auto GatesWrapperShell::add_gate(GatesT&& gates) -> void {
  insert_gate(std::cend(get_gates()), std::forward<GatesT>(gates));
}

template <class GateT, util::tmpl::enable_if_convertible_t<GateT, Gate>*>
auto GatesWrapperShell::insert_gate(GatesCIter pos, GateT&& gate) -> GatesIter {
  return get_gates().insert(pos, std::forward<GateT>(gate));
}

template <class GatesT,
          util::tmpl::enable_if_container_t<GatesT>*,
          util::tmpl::enable_if_lvalue_t<GatesT>*>
auto GatesWrapperShell::insert_gate(GatesCIter pos, GatesT&& gates)
  -> GatesIter {
  return get_gates().insert(pos, std::cbegin(gates), std::cend(gates));
}

template <class GatesT,
          util::tmpl::enable_if_container_t<GatesT>*,
          util::tmpl::enable_if_rvalue_t<GatesT>*>
auto GatesWrapperShell::insert_gate(GatesCIter pos, GatesT&& gates)
  -> GatesIter {
  return get_gates().insert(pos,
                            std::make_move_iterator(std::begin(gates)),
                            std::make_move_iterator(std::end(gates)));
}

template <class Predicate>
auto GatesWrapperShell::remove_gate_if(Predicate pred) -> void {
  get_gates().remove_if(pred);
}
}
