/**
 * @file warn_impl.hpp
 * @brief implementation header of Warning functions
 */

#pragma once

namespace qc {
namespace debug {
namespace warn {
inline auto set(bool enabled) -> bool {
  warn::enabled = enabled;
  return true;
}

inline auto set(bool enabled, std::ostream& os) -> bool {
  return warn::set(enabled) && warn::set(os);
}

inline auto set(bool enabled, std::ofstream&& ofs) -> bool {
  return warn::set(enabled) && warn::set(std::move(ofs));
}
}
}
}
