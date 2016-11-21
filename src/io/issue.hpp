/**
 * @file issue.hpp
 * @brief header of Issue functions
 */

#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
namespace error {
auto issue(const std::string& msg, const std::string& line,
           const std::string& filename, int line_count) -> void;
}

namespace warn {
auto issue(const std::string& msg, const std::string& line,
           const std::string& filename, int line_count) -> void;
}
}
}
