#pragma once

#include "../util/tmpl.hpp"

namespace qc {
namespace debug {
template <template <class...> class T, class... Args>
auto print(const T<Args...>& c, std::ostream& os, bool line_break) -> void {
  os << (util::tmpl::is_map_template<T>::value ? '{' : '[');
  for(const auto& e : c) {
    debug::print(e, os, false);
    os << ", ";
  }
  os << "\b\b" << (util::tmpl::is_map_template<T>::value ? '}' : ']');
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
