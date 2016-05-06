#include "../string.hpp"

namespace qc {
namespace util {
namespace string {
auto split(const std::string& str, const char delim, bool ignore_empty)
  -> std::vector<std::string> {
  std::vector<std::string> result;

  size_t current = 0;
  size_t found;

  while((found = str.find_first_of(delim, current)) != std::string::npos) {
    size_t length = found - current;
    if(!ignore_empty || length) result.emplace_back(str, current, length);
    current = found + 1;
  }
  size_t length = str.size() - current;
  if(!ignore_empty || length) result.emplace_back(str, current, length);

  return result;
}

auto isNumeric(const std::string& str) -> bool {
  if(str.empty()) return false;
  for(const auto& c : str) {
    if(!std::isdigit(c)) return false;
  }
  return true;
}

auto equalCaseInsensitive(const std::string& lhs, const std::string& rhs)
  -> bool {
  auto cmp = [](const char& lhs, const char& rhs) {
    std::locale locale;
    return std::tolower(lhs, locale) == std::tolower(rhs, locale);
  };
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), cmp);
}

auto getExtension(const std::string& filename) -> std::string {
  auto strs = util::string::split(filename, '.', false);
  if(strs.size() < 2) return std::string();
  return std::move(strs.back());
}

auto addExtension(const std::string& filename, const std::string& extension)
  -> std::string {
  if(extension == getExtension(filename)) return filename;
  return filename + "." + extension;
}
}
}
}
