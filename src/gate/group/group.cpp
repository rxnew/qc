#include "../group.hpp"

namespace qc {
constexpr char const* const GroupKernel::TYPE_NAME;

constexpr util::string::Aliases<6> const GroupKernel::ALIASES;

auto GroupKernel::print(std::ostream& os) const -> void {
  os << Group::BEGIN_TAG << std::endl;
  for(auto const& gate : get_gates()) {
    gate.print(os);
  }
  os << Group::END_TAG << std::endl;
}

auto GroupKernel::_get_cbits() const -> CBits& {
  m_cbits_.clear();
  for(auto const& gate : gates_) {
    for(auto const& cbit : gate.get_cbits()) {
      m_cbits_.insert(cbit);
    }
  }
  return m_cbits_;
}

auto GroupKernel::_get_tbits() const -> TBits& {
  m_tbits_.clear();
  for(auto const& gate : gates_) {
    for(auto const& tbit : gate.get_tbits()) {
      m_tbits_.insert(tbit);
    }
  }
  return m_tbits_;
}

constexpr char const* const GateType<GroupKernel>::BEGIN_TAG;

constexpr char const* const GateType<GroupKernel>::END_TAG;
}