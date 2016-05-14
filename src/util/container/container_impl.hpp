#pragma once

#include <algorithm>
#include <cassert>

namespace qc {
namespace util {
namespace container {
template <template <class...> class U, class T>
inline constexpr auto convert(const T& c) -> U<typename T::value_type> {
  return std::move(U<typename T::value_type>(c.cbegin(), c.cend()));
}

template <template <class...> class U, class T>
inline constexpr auto convertMap(const T& c)
  -> U<typename T::key_type, typename T::mapped_type> {
  return std::move(
    U<typename T::key_type, typename T::mapped_type>(c.cbegin(), c.cend()));
}

template <class E, class T>
auto toMap(const T& c, const E& e)
  -> std::map<typename T::value_type, E> {
  std::map<typename T::value_type, E> m;
  for(const auto& k : c) {
    m.insert(std::make_pair(k, e));
  }
  return std::move(m);
}

template <class E, class T>
inline auto toMap(const T& c) -> std::map<typename T::value_type, E> {
  return container::toMap(c, E());
}

template <template <class...> class T, class E>
auto isIntersected(const T<E>& lhs, const T<E>& rhs) -> bool {
  for(const auto& e : lhs) {
    if(std::find(rhs.cbegin(), rhs.cend(), e) != rhs.cend()) return true;
  }
  return false;
}

template <class E>
inline auto isIntersected(const std::set<E>& lhs,
                          const std::set<E>& rhs) -> bool {
  return container::isIntersectedSet(lhs, rhs);
}

template <class E>
inline auto isIntersected(const std::unordered_set<E>& lhs,
                          const std::unordered_set<E>& rhs) -> bool {
  return container::isIntersectedSet(lhs, rhs);
}

template <class T>
auto isIntersectedSet(const T& lhs, const T& rhs) -> bool {
  const auto cmp = [&lhs, &rhs]() {return lhs.size() < rhs.size();};
  const auto& tmp1 = cmp() ? lhs : rhs;
  const auto& tmp2 = cmp() ? rhs : lhs;
  for(const auto& e : tmp1) {
    if(tmp2.find(e) != tmp2.cend()) return true;
  }
  return false;
}

template <template <class...> class T, class E>
auto Compare::operator()(const T<E>& lhs, const T<E>& rhs) -> bool {
  auto it_l = lhs.cbegin(); 
  auto it_r = rhs.cbegin();
  while(true) {
    if(it_l == lhs.cend()) return true;
    if(it_r == rhs.cend()) return false;
    if(*it_l < *it_r) return true;
    if(*it_l > *it_r) return false;
    it_l++, it_r++;
  }
  assert(false);
  return false;
}

template <class E>
auto Compare::operator()(const std::unordered_set<E>& lhs,
                         const std::unordered_set<E>& rhs) -> bool {
  const auto ordered_lhs = container::convert<std::set>(lhs);
  const auto ordered_rhs = container::convert<std::set>(rhs);
  return ordered_lhs < ordered_rhs;
}
}
}
}
