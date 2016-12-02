#pragma once

#include <vector>
#include <string>
#include <tuple>

#include "string/basic_string.hpp"
#include "string/aliases.hpp"

namespace qc {
namespace util {
namespace string {
template <class CharT>
constexpr auto to_lower(CharT c) -> CharT;
template <class CharT>
constexpr auto to_upper(CharT c) -> CharT;
template <class T>
auto to_string(T&& arg, int precision = -1) -> std::string;
template <class... Args>
auto format(std::string const& str, Args&&... args) -> std::string;
auto split(std::string const& str, char const* const delim = " \t",
           bool const ignore_empty = true) -> std::vector<std::string>;
auto split(std::string const& str, char const delim,
           bool const ignore_empty = true) -> std::vector<std::string>;
auto split(std::string const& str, std::string const& delim,
           bool const ignore_empty = true) -> std::vector<std::string>;
auto trim_white_spaces(std::string const& str) -> std::string;
auto trim_comments(std::string const& str, char const tag = '#') -> std::string;
auto trim_comments(std::string const& str, std::string const& tag)
  -> std::string;
auto is_numeric(std::string const& str) -> bool;
auto equal_case_insensitive(std::string const& lhs, std::string const& rhs)
  -> bool;
auto splitext(std::string const& filename)
  -> std::tuple<std::string, std::string>;
auto basename(std::string const& filename) -> std::string;
auto dirname(std::string const& filename) -> std::string;
auto get_extension(std::string const& filename) -> std::string;
auto add_extension(std::string const& filename, std::string const& extension)
  -> std::string;
auto exclude_extension(std::string const& filename) -> std::string;
}
}
}

#include "string/string_impl.hpp"
