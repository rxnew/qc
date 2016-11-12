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
  return error::set(enabled) && error::set(os);
}

inline auto set(bool enabled, std::ofstream&& ofs) -> bool {
  return error::set(enabled) && error::set(std::move(ofs));
}
}
}
}
