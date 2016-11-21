#include "../error.hpp"

namespace qc {
namespace debug {
namespace error {
bool enabled = true;
std::ofstream ofs;
std::ostream* os = &std::cerr;

auto issue(std::string const& msg) -> void {
  if(!error::enabled) return;
  *error::os << "\x1b[31m"
             << "error: "
             << "\x1b[0m"
             << msg
             << std::endl;
}

auto set(std::ostream& os) -> bool {
  if(&os != &std::cout && &os != &std::cerr) return false;
  error::os = &os;
  return true;
}

auto set(std::ofstream&& ofs) -> bool {
  error::ofs = std::move(ofs);
  error::os = &error::ofs;
  return true;
}
}
}
}
