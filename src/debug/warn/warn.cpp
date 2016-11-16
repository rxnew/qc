#include "../warn.hpp"

namespace qc {
namespace debug {
namespace warn {
bool enabled = true;
std::ofstream ofs;
std::ostream* os = &std::cerr;

auto issue(std::string const& msg) -> void {
  if(!warn::enabled) return;
  *warn::os << "\x1b[34m"
            << "warning: "
            << "\x1b[0m"
            << msg
            << std::endl;
}

auto set(std::ostream& os) -> bool {
  if(&os != &std::cout && &os != &std::cerr) return false;
  warn::os = &os;
  return true;
}

auto set(std::ofstream&& ofs) -> bool {
  warn::ofs = std::move(ofs);
  warn::os = &warn::ofs;
  return true;
}
}
}
}
