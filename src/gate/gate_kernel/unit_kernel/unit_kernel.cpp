#include "../unit_kernel.hpp"

#include "../../../gate.hpp"
#include "../../../debug/assert.hpp"
#include "../../../util/container.hpp"
#include "../../../util/string.hpp"

namespace qc {
auto UnitKernel::get_gates() -> Gates& {
  assert_m(false, util::string::format
    ("This gate type is not 'Group', but '%s'.", get_type_name()).c_str());
  static auto gates = Gates();
  return gates;
}

auto UnitKernel::get_gates() const -> Gates const& {
  assert_m(false, util::string::format
    ("This gate type is not 'Group', but '%s'.", get_type_name()).c_str());
  static auto const gates = Gates();
  return gates;
}

auto UnitKernel::print(std::ostream& os) const -> void {
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

auto UnitKernel::print_simple(std::ostream& os, bool line_break) const -> void {
  auto ordered_cbits = util::container::convert<std::set>(cbits_);
  auto ordered_tbits = util::container::convert<std::set>(tbits_);

  os << get_type_name();
  os << '(';
  auto first = true;
  for(auto const& cbit : ordered_cbits) {
    if(!first) os << ',';
    else first = false;
    os << cbit;
  }
  for(auto const& tbit : ordered_tbits) {
    if(!first) os << ',';
    else first = false;
    os << tbit;
  }
  os << ')';
  if(line_break) os << std::endl;
}
}
