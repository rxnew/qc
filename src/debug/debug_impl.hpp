#pragma once

#include "../util/tmpl.hpp"

namespace qc {
namespace debug {
template <template <class...> class T, class... Args>
auto print(const T<Args...>& c, std::ostream& os, bool line_break) -> void {
  const auto is_curly_bracket = []() {
    return util::tmpl::is_set_template<T>::value ||
           util::tmpl::is_map_template<T>::value;
  };
  os << (is_curly_bracket() ? '{' : '[');
  for(const auto& e : c) {
    debug::print(e, os, false);
    os << ", ";
  }
  os << "\b\b" << (is_curly_bracket() ? '}' : ']');
  if(line_break) os << std::endl;
}

template <class E>
auto print(const E& e, std::ostream& os, bool line_break) -> void {
  os << e;
  if(line_break) os << std::endl;
}

template <class K, class V>
auto print(const std::pair<K, V>& p, std::ostream& os, bool line_break)
  -> void {
  debug::print(p.first, os, false);
  os << ": ";
  debug::print(p.second, os, false);
  if(line_break) os << std::endl;
}
}
}
