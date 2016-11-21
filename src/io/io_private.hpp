/**
 * @file io_private.hpp
 * @brief private header of qc::io methods
 */

#pragma once

#include <ios>

#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
auto _get_unknown_format_message(std::string const& extension)
  -> std::string;
auto _get_not_support_format_message(std::string const& extension,
                                     std::string const& method_name)
  -> std::string;
auto _get_unknown_format_exception(std::string const& extension)
  -> std::ios_base::failure;
auto _get_not_support_format_exception(std::string const& extension,
                                       std::string const& method_name)
  -> exc::IllegalFormatException;
}
}

// implementation
namespace qc {
namespace io {
inline auto _get_unknown_format_message(std::string const& extension)
  -> std::string {
  return "Unknown format: '" + extension + "'.";
}

inline auto _get_not_support_format_message(std::string const& extension,
                                            std::string const& method_name)
  -> std::string {
  return "'" + method_name + "()' not supports format: '" + extension + "'.";
}

inline auto _get_unknown_format_exception(std::string const& extension)
  -> std::ios_base::failure {
  return std::ios_base::failure(
    _get_unknown_format_message(extension));
}

inline auto _get_not_support_format_exception(std::string const& extension,
                                              std::string const& method_name)
  -> exc::IllegalFormatException {
  return exc::IllegalFormatException(
    _get_not_support_format_message(extension, method_name));
}
}
}
