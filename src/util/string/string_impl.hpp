#pragma once

#include <iomanip>
#include <regex>
#include <sstream>

// Private methods
namespace qc {
namespace util {
namespace string {
template <class T>
auto _formatOne(std::ostringstream& os, std::string::const_iterator& it,
                T&& arg) -> void;

template <class T>
auto _format(std::ostringstream& os, std::string::const_iterator& it,
             T&& arg) -> void;

template <class T, class... Args>
auto _format(std::ostringstream& os, std::string::const_iterator& it,
             T&& arg, Args&&... args) -> void;
}
}
}

namespace qc {
namespace util {
namespace string {
template <class T>
auto toString(T&& arg, int precision) -> std::string {
  std::ostringstream os;
  os << std::fixed;
  if(precision != -1) os << std::setprecision(precision);
  os << arg;
  return os.str();
}

template <class... Args>
auto format(const std::string& str, Args&&... args) -> std::string {
  std::ostringstream os;
  auto it = str.cbegin();
  string::_format(os, it, std::forward<Args>(args)...);
  return os.str();
}

inline auto split(const std::string& str, const char* delim,
                  const bool ignore_empty) -> std::vector<std::string> {
  return string::split(str, std::string(delim), ignore_empty);
}

inline auto split(const std::string& str, const char delim,
                  const bool ignore_empty) -> std::vector<std::string> {
  return string::split(str, std::string(1, delim), ignore_empty);
}

inline auto trimWhiteSpaces(const std::string& str) -> std::string {
  const std::regex re_f(R"(^[ \t]*)");
  const std::regex re_b(R"([ \t]*$)");
  return std::regex_replace(std::regex_replace(str, re_f, ""), re_b, "");
}

inline auto trimComments(const std::string& str,
                         const char tag) -> std::string {
  return trimComments(str, std::string(1, tag));
}

inline auto trimComments(const std::string& str,
                         const std::string& tag) -> std::string {
  const std::regex re(tag + R"(.*$)");
  return std::regex_replace(str, re, "");
}

inline auto getExtension(const std::string& filename) -> std::string {
  return std::move(std::get<1>(string::splitext(filename)));
}

inline auto addExtension(const std::string& filename,
                         const std::string& extension) -> std::string {
  if(extension == string::getExtension(filename)) return filename;
  return std::move(filename + "." + extension);
}

inline auto excludeExtension(const std::string& filename) -> std::string {
  return std::move(std::get<0>(string::splitext(filename)));
}

template <class T>
auto _formatOne(std::ostringstream& os, std::string::const_iterator& it,
                T&& arg) -> void {
  while(*it) {
    if(*it == '%') {
      auto next = *++it;
      if(next == 'd' || next == 'f' || next == 's') {
        os << string::toString(std::forward<T>(arg));
        it++;
        return;
      }
    }
    os << *it++;
  }
}

template <class T>
auto _format(std::ostringstream& os, std::string::const_iterator& it,
             T&& arg) -> void {
  string::_formatOne(os, it, arg);
  while(*it) os << *it++;
}

template <class T, class... Args>
auto _format(std::ostringstream& os, std::string::const_iterator& it,
             T&& arg, Args&&... args) -> void {
  string::_formatOne(os, it, arg);
  string::_format(os, it, std::forward<Args>(args)...);
}
}
}
}
