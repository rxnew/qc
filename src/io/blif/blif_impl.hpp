/**
 * @file blif_impl.hpp
 * @brief implementation header of qc::io::Blif class
 */

#pragma once

#include "../../algorithm/oracle.hpp"

namespace qc {
namespace io {
inline auto Blif::_getErrorMessage(const std::string& code)
  -> const std::string& {
  return Blif::_err_msgs.at(code);
}

inline auto Blif::_getWarnMessage(const std::string& code)
  -> const std::string& {
  return Blif::_warn_msgs.at(code);
}
}
}
