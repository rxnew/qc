#pragma once

#include <vector>
#include <string>

namespace util {
struct StringHelper {
  static auto split(const std::string& str, const char delim = ' ')
    -> std::vector<std::string>;
  static auto isNumeric(const std::string& str) -> bool;
};
}
