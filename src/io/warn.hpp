/**
 * @file warn.hpp
 * @brief header of Warning functions
 */

#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace qc {
namespace io {
namespace warn {
extern bool enabled;

auto issue(const std::string& msg) -> void;
auto issue(const std::string& msg, const std::string& filename,
           int line_count) -> void;
auto set(bool enabled) -> bool;
auto set(std::ostream& os) -> bool;
auto set(std::ofstream&& ofs) -> bool;
auto set(bool enabled, std::ostream& os) -> bool;
auto set(bool enabled, std::ofstream&& ofs) -> bool;
};
}
}

#include "warn/warn_impl.hpp"
