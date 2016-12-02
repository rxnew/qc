#include "../gates_wrapper_shell.hpp"
#include "../../../gate.hpp"

namespace qc {
auto GatesWrapperShell::set_gates(Gates&& gates) -> void {
  _get_gates() = std::move(gates);
}

auto GatesWrapperShell::erase_gate(GatesCIter pos) -> GatesIter {
  return _get_gates().erase(pos);
}

auto GatesWrapperShell::erase_gate(GatesIter pos, Gate& gate)
  -> GatesIter {
  gate = std::move(*pos);
  return erase_gate(pos);
}

auto GatesWrapperShell::erase_gate(GatesCIter first, GatesCIter last)
  -> GatesIter {
  return _get_gates().erase(first, last);
}

auto GatesWrapperShell::remove_gate(Gate const& gate) -> void {
  _get_gates().remove(gate);
}

auto GatesWrapperShell::move_gate(GatesCIter to, GatesIter from)
  -> GatesIter {
  insert_gate(to, std::move(*from));
  return erase_gate(from);
}

auto GatesWrapperShell::swap_gate(GatesIter pos_a, GatesIter pos_b)
  -> void {
  std::swap(*pos_a, *pos_b);
}

auto GatesWrapperShell::reverse_gate() noexcept -> void {
  _get_gates().reverse();
}

auto GatesWrapperShell::begin_gates() -> GatesIter {
  return std::begin(_get_gates());
}

auto GatesWrapperShell::end_gates() -> GatesIter {
  return std::end(_get_gates());
}

auto GatesWrapperShell::cbegin_gates() const -> GatesCIter {
  return std::cbegin(get_gates());
}

auto GatesWrapperShell::cend_gates() const -> GatesCIter {
  return std::cend(get_gates());
}

auto GatesWrapperShell::extend(GatesWrapperShell const& other)
  -> GatesWrapperShell& {
  add_gate(other.get_gates());
  return *this;
}

auto GatesWrapperShell::extend(GatesWrapperShell&& other)
  -> GatesWrapperShell& {
  add_gate(std::move(other.get_gates()));
  return *this;
}

auto GatesWrapperShell::clear() -> void {
  _get_gates().clear();
}

auto GatesWrapperShell::empty() const -> bool {
  return get_gates().empty();
}

auto GatesWrapperShell::get_gates_count() const -> size_t {
  return get_gates().size();
}

auto GatesWrapperShell::invert() -> void {
  for(auto& gate : _get_gates()) {
    gate.invert();
  }
  reverse_gate();
}

auto GatesWrapperShell::collect_bits() const -> BitNos {
  auto bit_nos = BitNos();
  for(auto const& gate : get_gates()) {
    auto const gate_bit_nos = gate.collect_bits();
    bit_nos.insert(gate_bit_nos.cbegin(), gate_bit_nos.cend());
  }
  return bit_nos;
}

auto GatesWrapperShell::print(std::ostream& os) const -> void {
  for(auto const& gate : get_gates()) {
    gate.print(os);
  }
}
}
