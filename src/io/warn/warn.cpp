#include "../warn.hpp"

namespace qc {
namespace io {
namespace warn {
bool enabled = true;
std::ofstream ofs;
std::ostream* os = &std::cerr;

auto issue(const std::string& msg) -> void {
  if(!warn::enabled) return;
  *warn::os << "\x1b[34m"
            << "warning: "
            << "\x1b[0m"
            << msg
            << std::endl;
}

auto issue(const std::string& msg, const std::string& filename,
           int line_count) -> void {
  if(!warn::enabled) return;
  *warn::os << filename
            << ":"
            << line_count
            << ": ";
  warn::issue(msg);
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
