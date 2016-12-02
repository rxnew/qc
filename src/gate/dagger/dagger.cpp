#include <regex>

#include "../dagger.hpp"

namespace qc {
constexpr char const* const regex_dagger_tag = R"((\*|\+|dagger|plus)$)";

auto type_name(std::string const& type_name, bool dagger) -> std::string {
  if(dagger) return append_dagger_tag(type_name);
  return type_name;
}

auto append_dagger_tag(std::string const& type_name) -> std::string {
  return type_name + DAGGER_TAG;
}

auto exclude_dagger_tag(std::string& type_name) -> bool {
  static auto const re =
    std::regex(regex_dagger_tag, std::regex_constants::icase);
  if(!std::regex_search(type_name, re)) return false;
  type_name = std::regex_replace(type_name, re, "");
  return true;
}
}
