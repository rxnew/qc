#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <locale>

namespace util {
struct StringHelper {
  static auto split(const std::string& str, \
                    const char delim = ' ', \
                    bool ignore_empty = true)
    -> std::vector<std::string>;
  static auto isNumeric(const std::string& str) -> bool;
  static auto equalCaseInsensitive(const std::string& lhs, \
                                   const std::string& rhs) -> bool;
};
}
