#include "../issue.hpp"

#include "../../debug/issue.hpp"

namespace qc {
namespace io {
namespace error {
auto issue(const std::string& msg, const std::string& line,
           const std::string& filename, int line_count)
  throw(exc::IllegalFormatException) -> void {
  if(!debug::error::enabled) return;

  *debug::error::os << filename
                    << ":"
                    << line_count
                    << ": ";
  debug::error::issue(msg + "\n  " + line);

  throw exc::IllegalFormatException(msg);
}
}

namespace warn {
auto issue(const std::string& msg, const std::string& line,
           const std::string& filename, int line_count) -> void {
  if(!debug::warn::enabled) return;

  *debug::warn::os << filename
                   << ":"
                   << line_count
                   << ": ";
  debug::warn::issue(msg + "\n  " + line);
}
}
}
}
