#include "string_helper.hpp"

namespace util {
auto StringHelper::split(const std::string& str, const char delim)
  -> std::vector<std::string> {
  std::vector<std::string> result;

  size_t current = 0;
  size_t found;
  size_t length;

  while((found = str.find_first_of(delim, current)) != std::string::npos) {
    length = found - current;
    if(length) result.emplace_back(str, current, length);
    current = found + 1;
  }
  length = str.size() - current;
  if(length) result.emplace_back(str, current, length);

  return result;
}

auto StringHelper::isNumeric(const std::string& str) -> bool {
  if(str.empty()) return false;
  for(const auto& c : str) {
    if(!std::isdigit(c)) return false;
  }
  return true;
}

auto StringHelper::equalCaseInsensitive(const std::string& lhs, \
                                        const std::string& rhs) -> bool {
  auto cmp = [](const char& lhs, const char& rhs) {
    std::locale locale;
    return std::tolower(lhs, locale) == std::tolower(rhs, locale);
  };
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), cmp);
}
}
