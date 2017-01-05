#pragma once

namespace qc {
namespace debug {
template <template <class...> class T, class... Args, class>
auto print(T<Args...> const& c, std::ostream& os, bool line_break) -> void {
  auto const is_curly_bracket = []() {
    return util::tmpl::is_set_template<T>::value ||
           util::tmpl::is_map_template<T>::value;
  };
  os << (is_curly_bracket() ? '{' : '[');
  auto first = true;
  for(auto const& e : c) {
    if(!first) os << ',';
    else first = false;
    print(e, os, false);
  }
  os << (is_curly_bracket() ? '}' : ']');
  if(line_break) os << std::endl;
}

template <class E>
auto print(E const& e, std::ostream& os, bool line_break) -> void {
  os << e;
  if(line_break) os << std::endl;
}

template <class E>
auto print(E const* const& e, std::ostream& os, bool line_break) -> void {
  os << *e;
  if(line_break) os << std::endl;
}

template <class E>
auto print(std::unique_ptr<E> const& e, std::ostream& os, bool line_break)
  -> void {
  os << *e;
  if(line_break) os << std::endl;
}

template <class E>
auto print(std::shared_ptr<E> const& e, std::ostream& os, bool line_break)
  -> void {
  os << *e;
  if(line_break) os << std::endl;
}

template <class E>
auto print(std::weak_ptr<E> const& e, std::ostream& os, bool line_break)
  -> void {
  os << *e;
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
