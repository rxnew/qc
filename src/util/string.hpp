#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <locale>

namespace qc {
namespace util {
namespace string {
template <class T>
auto toString(T&& arg, int precision = -1) -> std::string;
template <class... Args>
auto format(const std::string& str, Args&&... args) -> std::string;
auto split(const std::string& str, const char* delim = " \t",
           const bool ignore_empty = true) -> std::vector<std::string>;
auto split(const std::string& str, const char delim,
           const bool ignore_empty = true) -> std::vector<std::string>;
auto split(const std::string& str, const std::string& delim,
           const bool ignore_empty = true) -> std::vector<std::string>;
auto trimWhiteSpaces(const std::string& str) -> std::string;
auto trimComments(const std::string& str, const char tag = '#') -> std::string;
auto trimComments(const std::string& str,
                  const std::string& tag) -> std::string;
auto isNumeric(const std::string& str) -> bool;
auto equalCaseInsensitive(const std::string& lhs,
                          const std::string& rhs) -> bool;
auto splitext(const std::string& filename)
  -> std::tuple<std::string, std::string>;
auto basename(const std::string& filename) -> std::string;
auto dirname(const std::string& filename) -> std::string;
auto getExtension(const std::string& filename) -> std::string;
auto addExtension(const std::string& filename,
                  const std::string& extension) -> std::string;
auto excludeExtension(const std::string& filename) -> std::string;
}
}
}

#include "string/string_impl.hpp"
