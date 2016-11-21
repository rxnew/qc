/**
 * @file error_impl.hpp
 * @brief implementation header of Error functions
 */

#pragma once

namespace qc {
namespace debug {
namespace error {
inline auto set(bool enabled) -> bool {
  error::enabled = enabled;
  return true;
}

inline auto set(bool enabled, std::ostream& os) -> bool {
  return set(enabled) && set(os);
}

inline auto set(bool enabled, std::ofstream&& ofs) -> bool {
  return set(enabled) && set(std::move(ofs));
}
}
}
}
