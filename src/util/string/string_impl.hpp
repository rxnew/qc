#pragma once

#include <iomanip>
#include <regex>
#include <sstream>

// Private methods
namespace qc {
namespace util {
namespace string {
template <class T>
auto _format_one(std::ostringstream& os, std::string::const_iterator& it,
                 T&& arg) -> void;

template <class T>
auto _format(std::ostringstream& os, std::string::const_iterator& it, T&& arg)
  -> void;

template <class T, class... Args>
auto _format(std::ostringstream& os, std::string::const_iterator& it, T&& arg,
             Args&&... args) -> void;
}
}
}

namespace qc {
namespace util {
namespace string {
template <class T>
auto to_string(T&& arg, int precision) -> std::string {
  auto os = std::ostringstream();
  os << std::fixed;
  if(precision != -1) os << std::setprecision(precision);
  os << arg;
  return os.str();
}

template <class... Args>
auto format(std::string const& str, Args&&... args) -> std::string {
  auto os = std::ostringstream();
  auto it = str.cbegin();
  _format(os, it, std::forward<Args>(args)...);
  return os.str();
}

inline auto split(std::string const& str, char const* const delim,
                  bool const ignore_empty) -> std::vector<std::string> {
  return split(str, std::string(delim), ignore_empty);
}

inline auto split(std::string const& str, char const delim,
                  bool const ignore_empty) -> std::vector<std::string> {
  return split(str, std::string(1, delim), ignore_empty);
}

inline auto trim_white_spaces(std::string const& str) -> std::string {
  std::regex const re_f(R"(^[ \t]*)");
  std::regex const re_b(R"([ \t]*$)");
  return std::regex_replace(std::regex_replace(str, re_f, ""), re_b, "");
}

inline auto trim_comments(std::string const& str, char const tag)
  -> std::string {
  return trim_comments(str, std::string(1, tag));
}

inline auto trim_comments(std::string const& str, std::string const& tag)
  -> std::string {
  std::regex const re(tag + R"(.*$)");
  return std::regex_replace(str, re, "");
}

inline auto get_extension(std::string const& filename) -> std::string {
  return std::get<1>(splitext(filename));
}

inline auto add_extension(std::string const& filename,
                          std::string const& extension) -> std::string {
  if(extension == get_extension(filename)) return filename;
  return filename + "." + extension;
}

inline auto exclude_extension(std::string const& filename) -> std::string {
  return std::get<0>(string::splitext(filename));
}

template <class T>
auto _format_one(std::ostringstream& os, std::string::const_iterator& it,
                 T&& arg) -> void {
  while(*it) {
    if(*it == '%') {
      auto next = *++it;
      if(next == 'd' || next == 'f' || next == 's') {
        os << to_string(std::forward<T>(arg));
        it++;
        return;
      }
    }
    os << *it++;
  }
}

template <class T>
auto _format(std::ostringstream& os, std::string::const_iterator& it, T&& arg)
  -> void {
  _format_one(os, it, arg);
  while(*it) os << *it++;
}

template <class T, class... Args>
auto _format(std::ostringstream& os, std::string::const_iterator& it, T&& arg,
             Args&&... args) -> void {
  _format_one(os, it, arg);
  _format(os, it, std::forward<Args>(args)...);
}
}
}
}
