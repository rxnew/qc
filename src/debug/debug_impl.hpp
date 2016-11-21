#pragma once

#include "../util/tmpl.hpp"

namespace qc {
namespace debug {
template <template <class...> class T, class... Args>
auto print(T<Args...> const& c, std::ostream& os, bool line_break) -> void {
  auto const is_curly_bracket = []() {
    return util::tmpl::is_set_template<T>::value ||
           util::tmpl::is_map_template<T>::value;
  };
  os << (is_curly_bracket() ? '{' : '[');
  for(auto const& e : c) {
    print(e, os, false);
    os << ", ";
  }
  os << "\b\b" << (is_curly_bracket() ? '}' : ']');
  if(line_break) os << std::endl;
}

template <class E>
auto print(E const& e, std::ostream& os, bool line_break) -> void {
  os << e;
  if(line_break) os << std::endl;
}

template <class K, class V>
auto print(std::pair<K, V> const& p, std::ostream& os, bool line_break)
  -> void {
  print(p.first, os, false);
  os << ": ";
  print(p.second, os, false);
  if(line_break) os << std::endl;
}
}
}
