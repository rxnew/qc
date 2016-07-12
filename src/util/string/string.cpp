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

auto splitext(const std::string& filename)
  -> std::tuple<std::string, std::string> {
  auto found = filename.find_last_of("./");
  if(found == std::string::npos || filename[found] == '/') {
    return std::move(std::make_tuple(filename, std::string()));
  }
  auto path = filename.substr(0, found);
  auto extension = filename.substr(found);
  return std::move(std::make_tuple(path, extension));
}

auto basename(const std::string& filename) -> std::string {
  auto found = filename.find_last_of("/");
  if(found == std::string::npos) return filename;
  return std::move(filename.substr(found + 1));
}

auto dirname(const std::string& filename) -> std::string {
  auto found = filename.find_last_of("/");
  if(found == std::string::npos) return std::move(std::string());
  return std::move(filename.substr(0, found));
}
}
}
}
