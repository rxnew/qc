#include "../group.hpp"

namespace qc {
constexpr char const* const Group::TYPE_NAME = "Group";
constexpr util::string::Aliases<6> const Group::ALIASES = {
  "group",
  "module",
  "macrogate",
  "gatearray",
  "step",
  "pqgate"
};
constexpr char const* const Group::BEGIN_TAG = "<Group>";
constexpr char const* const Group::END_TAG = "</Group>";

auto Group::make(std::initializer_list<Gate> list) -> Gate {
  auto gate = Gate::make_dummy(false);
  GateType::_get_impl(gate) = std::make_unique<Impl>(list);
  return gate;
}

auto Group::Impl::print(std::ostream& os) const -> void {
  os << BEGIN_TAG << std::endl;
  for(auto const& gate : gates_) {
    gate.print(os);
  }
  os << END_TAG << std::endl;
}

auto Group::Impl::_get_cbits() const -> CBits& {
  m_cbits_.clear();
  for(auto const& gate : gates_) {
    for(auto const& cbit : gate.get_cbits()) {
      m_cbits_.insert(cbit);
    }
  }
  return m_cbits_;
}

auto Group::Impl::_get_tbits() const -> TBits& {
  m_tbits_.clear();
  for(auto const& gate : gates_) {
    for(auto const& tbit : gate.get_tbits()) {
      m_tbits_.insert(tbit);
    }
  }
  return m_tbits_;
}
}
