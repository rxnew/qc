#pragma once

#include <regex>

namespace qc {
inline namespace constants {
inline namespace gate_constants {
constexpr bool const bedaggered = true;
constexpr char const* const DAGGER_TAG = "*";
}
}

auto type_name(std::string const& type_name, bool bedaggered = false)
  -> std::string;
auto append_bedaggered_tag(std::string const& type_name) -> std::string;
auto exclude_bedaggered_tag(std::string& type_name) -> bool;
}
