#pragma once

#include <algorithm>
#include <cassert>

namespace qc {
namespace util {
namespace container {
template <template <class...> class U, class T>
inline auto convert(T const& c) -> U<typename T::value_type> {
  return U<typename T::value_type>(c.cbegin(), c.cend());
}

template <template <class...> class U, class K, class V>
inline auto convert(std::map<K, V> const& c) -> U<K, V> {
  return U<K, V>(c.cbegin(), c.cend());
}

template <template <class...> class U, class K, class V>
inline auto convert(std::unordered_map<K, V> const& c) -> U<K, V> {
  return U<K, V>(c.cbegin(), c.cend());
}

template <template <class...> class T, class E>
inline auto ordered(T<E> const& c) -> std::set<E> {
  return convert<std::set>(c);
}

template <class K, class V>
inline auto ordered(std::unordered_map<K, V> const& c) -> std::map<K, V> {
  return convert<std::map>(c);
}

template <class E, class T>
auto to_map(T const& c, E const& e) -> std::map<typename T::value_type, E> {
  auto m = std::map<typename T::value_type, E>();
  for(auto const& k : c) {
    m.emplace(k, e);
  }
  return m;
}

template <class E, class T>
inline auto to_map(T const& c) -> std::map<typename T::value_type, E> {
  return to_map(c, E());
}

template <template <class...> class T, class E>
auto is_intersected(T<E> const& lhs, T<E> const& rhs) -> bool {
  for(auto const& e : lhs) {
    if(std::find(rhs.cbegin(), rhs.cend(), e) != rhs.cend()) return true;
  }
  return false;
}

template <class E>
inline auto is_intersected(std::set<E> const& lhs, std::set<E> const& rhs)
  -> bool {
  return is_intersected_set(lhs, rhs);
}

template <class E>
inline auto is_intersected(std::unordered_set<E> const& lhs,
                           std::unordered_set<E> const& rhs) -> bool {
  return is_intersected_set(lhs, rhs);
}

template <class T>
auto is_intersected_set(T const& lhs, T const& rhs) -> bool {
  auto const cmp = [&lhs, &rhs] {return lhs.size() < rhs.size();};
  auto const& tmp1 = cmp() ? lhs : rhs;
  auto const& tmp2 = cmp() ? rhs : lhs;
  for(auto const& e : tmp1) {
    if(tmp2.find(e) != tmp2.cend()) return true;
  }
  return false;
}

template <template <class...> class T, class E, class ECompare>
auto Compare::operator()(T<E> const& lhs, T<E> const& rhs,
                         ECompare const& cmp) const -> bool {
  auto it_l = lhs.cbegin(); 
  auto it_r = rhs.cbegin();
  while(true) {
    if(it_r == rhs.cend()) return false;
    if(it_l == lhs.cend()) return true;
    if(cmp(*it_r, *it_l)) return false;
    if(cmp(*it_l, *it_r)) return true;
    it_l++, it_r++;
  }
  assert(false);
  return false;
}

template <class E, class ECompare>
auto Compare::operator()(std::unordered_set<E> const& lhs,
                         std::unordered_set<E> const& rhs,
                         ECompare const& cmp) const -> bool {
  auto const ordered_lhs = convert<std::set>(lhs);
  auto const ordered_rhs = convert<std::set>(rhs);
  return operator()(ordered_lhs, ordered_rhs, cmp);
}
}
}
}
