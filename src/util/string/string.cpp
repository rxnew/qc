#include "../string.hpp"

#include <locale>

namespace qc {
namespace util {
namespace string {
auto split(std::string const& str, std::string const& delim,
           bool const ignore_empty) -> std::vector<std::string> {
  auto result = std::vector<std::string>();

  auto current = size_t(0);
  auto found = size_t();

  while((found = str.find_first_of(delim, current)) != std::string::npos) {
    auto length = found - current;
    if(!ignore_empty || length) result.emplace_back(str, current, length);
    current = found + 1;
  }
  auto length = str.size() - current;
  if(!ignore_empty || length) result.emplace_back(str, current, length);

  return result;
}

auto is_numeric(std::string const& str) -> bool {
  if(str.empty()) return false;
  for(auto const& c : str) {
    if(!std::isdigit(c)) return false;
  }
  return true;
}

auto equal_case_insensitive(std::string const& lhs, std::string const& rhs)
  -> bool {
  auto const cmp = [](char const& lhs, char const& rhs) {
    auto locale = std::locale();
    return std::tolower(lhs, locale) == std::tolower(rhs, locale);
  };
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), cmp);
}

auto splitext(std::string const& filename)
  -> std::tuple<std::string, std::string> {
  auto found = filename.find_last_of("./");
  if(found == std::string::npos || filename[found] == '/') {
    return std::make_tuple(filename, std::string());
  }
  auto path = filename.substr(0, found);
  auto extension = filename.substr(found);
  return std::make_tuple(path, extension);
}

auto basename(std::string const& filename) -> std::string {
  auto found = filename.find_last_of("/");
  if(found == std::string::npos) return filename;
  return filename.substr(found + 1);
}

auto dirname(std::string const& filename) -> std::string {
  auto found = filename.find_last_of("/");
  if(found == std::string::npos) return std::string();
  return filename.substr(0, found);
}
}
}
}
