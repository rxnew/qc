/**
 * @file blif_impl.hpp
 * @brief implementation header of qc::io::Blif class
 */

#pragma once

#include "../../algorithm/oracle.hpp"

namespace qc {
namespace io {
inline auto Blif::_get_error_message(std::string const& code)
  -> std::string const& {
  return _err_msgs.at(code);
}

inline auto Blif::_get_warn_message(std::string const& code)
  -> std::string const& {
  return _warn_msgs.at(code);
}
}
}
