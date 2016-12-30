/**
 * @file json_impl.hpp
 * @brief implementation header of qc::io::Json class
 */

#pragma once

#include "../../algorithm/oracle.hpp"

namespace qc {
namespace io {
inline auto Json::_get_error_message(std::string const& code)
  -> std::string const& {
  return _err_msgs.at(code);
}

inline auto Json::_get_warn_message(std::string const& code)
  -> std::string const& {
  return _warn_msgs.at(code);
}
}
}
