/**
 * @file error.hpp
 * @brief header of Error functions
 */

#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace qc {
namespace debug {
namespace error {
extern bool enabled;
extern std::ostream* os;

auto issue(std::string const& msg) -> void;
auto set(bool enabled) -> bool;
auto set(std::ostream& os) -> bool;
auto set(std::ofstream&& ofs) -> bool;
auto set(bool enabled, std::ostream& os) -> bool;
auto set(bool enabled, std::ofstream&& ofs) -> bool;
};
}
}

#include "error/error_impl.hpp"
