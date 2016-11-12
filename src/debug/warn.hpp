/**
 * @file warn.hpp
 * @brief header of Warning functions
 */

#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace qc {
namespace debug {
namespace warn {
extern bool enabled;
extern std::ostream* os;

auto issue(const std::string& msg) -> void;
auto set(bool enabled) -> bool;
auto set(std::ostream& os) -> bool;
auto set(std::ofstream&& ofs) -> bool;
auto set(bool enabled, std::ostream& os) -> bool;
auto set(bool enabled, std::ofstream&& ofs) -> bool;
};
}
}

#include "warn/warn_impl.hpp"
