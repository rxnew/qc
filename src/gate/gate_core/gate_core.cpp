#include "../gate_core.hpp"

#include "../../gate.hpp"
#include "../../util/container.hpp"

namespace qc {
auto GateCore::print(std::ostream& os) const -> void {
  auto ordered_cbits = util::container::convert<std::set>(cbits_);
  auto ordered_tbits = util::container::convert<std::set>(tbits_);

  os << get_type_name();
  os << R"( \)";
  for(auto const& cbit : ordered_cbits) {
    os << ' ' << cbit;
  }
  for(auto const& tbit : ordered_tbits) {
    os << ' ' << tbit;
  }
  os << R"( \)";
  //os << ' ' << this->getVariable();
  os << R"( \)";
  //os << ' ' << this->getFunction();
  os << std::endl;
}

auto GateCore::get_gates() -> Gates& {
  assert(!"not a group");
  static auto gates = Gates();
  return gates;
}

auto GateCore::get_gates() const -> Gates const& {
  assert(!"not a group");
  static auto const gates = Gates();
  return gates;
}
}
