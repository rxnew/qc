/**
 * @file io_private.hpp
 * @brief private header of qc::io methods
 */

#pragma once

#include <ios>

#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
auto _getUnknownFormatMessage(const std::string& extension)
  -> std::string;
auto _getNotSupportFormatMessage(const std::string& extension,
                                 const std::string& method_name)
  -> std::string;
auto _getUnknownFormatException(const std::string& extension)
  -> std::ios_base::failure;
auto _getNotSupportFormatException(const std::string& extension,
                                   const std::string& method_name)
  -> exc::IllegalFormatException;
}
}

// implementation
namespace qc {
namespace io {
inline auto _getUnknownFormatMessage(const std::string& extension)
  -> std::string {
  return "Unknown format: '." + extension + "'.";
}

inline auto _getNotSupportFormatMessage(const std::string& extension,
                                        const std::string& method_name)
  -> std::string {
  return "'" + method_name + "()' not supports format: '." + extension + "'.";
}

inline auto _getUnknownFormatException(const std::string& extension)
  -> std::ios_base::failure {
  return std::ios_base::failure(
    _getUnknownFormatMessage(extension));
}

inline auto _getNotSupportFormatException(const std::string& extension,
                                          const std::string& method_name)
  -> exc::IllegalFormatException {
  return exc::IllegalFormatException(
    _getNotSupportFormatMessage(extension, method_name));
}
}
}
