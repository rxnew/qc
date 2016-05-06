#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <locale>

namespace qc {
namespace util {
namespace string {
auto split(const std::string& str, const char delim = ' ',
           bool ignore_empty = true)
  -> std::vector<std::string>;
auto isNumeric(const std::string& str) -> bool;
auto equalCaseInsensitive(const std::string& lhs, const std::string& rhs)
  -> bool;
auto getExtension(const std::string& filename) -> std::string;
auto addExtension(const std::string& filename, const std::string& extension)
  -> std::string;
}
}
}
