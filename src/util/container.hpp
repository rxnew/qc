#pragma once

#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

namespace qc {
namespace util {
namespace container {
template <template <class...> class U, class T>
auto convert(const T& c) -> U<typename T::value_type>;

template <template <class...> class U, class K, class V>
auto convert(const std::map<K, V>& c) -> U<K, V>;

template <template <class...> class U, class K, class V>
auto convert(const std::unordered_map<K, V>& c) -> U<K, V>;

template <class E, class T>
auto toMap(const T& c, const E& e) -> std::map<typename T::value_type, E>;

template <class E, class T>
auto toMap(const T& c) -> std::map<typename T::value_type, E>;

template <template <class...> class T, class E>
auto isIntersected(const T<E>& lhs, const T<E>& rhs) -> bool;

template <class E>
auto isIntersected(const std::set<E>& lhs, const std::set<E>& rhs) -> bool;

template <class E>
auto isIntersected(const std::unordered_set<E>& lhs,
                   const std::unordered_set<E>& rhs) -> bool;

template <class T>
inline auto isIntersectedSet(const T& lhs, const T& rhs) -> bool;

struct Compare {
  template <template <class...> class T, class E,
            class ECompare = std::less<E>>
  auto operator()(const T<E>& lhs, const T<E>& rhs,
                  const ECompare& cmp = ECompare()) const -> bool;

  template <class E, class ECompare = std::less<E>>
  auto operator()(const std::unordered_set<E>& lhs,
                  const std::unordered_set<E>& rhs,
                  const ECompare& cmp = ECompare()) const -> bool;
};
}
}
}

#include "container/container_impl.hpp"
