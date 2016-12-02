#include "../group_kernel.hpp"

#include "../../group.hpp"

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
  static auto cbits = CBits();

  cbits.clear();
  for(auto const& gate : gates_) {
    for(auto const& cbit : gate.get_cbits()) {
      cbits.insert(cbit);
    }
  }
  return cbits;
}

auto GroupKernel::_get_tbits() const -> TBits& {
  static auto tbits = TBits();

  tbits.clear();
  for(auto const& gate : gates_) {
    for(auto const& tbit : gate.get_tbits()) {
      tbits.insert(tbit);
    }
  }
  return tbits;
}
}
