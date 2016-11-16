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
auto convert(T const& c) -> U<typename T::value_type>;

template <template <class...> class U, class K, class V>
auto convert(std::map<K, V> const& c) -> U<K, V>;

template <template <class...> class U, class K, class V>
auto convert(std::unordered_map<K, V> const& c) -> U<K, V>;

template <template <class...> class T, class E>
auto ordered(T<E> const& c) -> std::set<E>;

template <class K, class V>
auto ordered(std::unordered_map<K, V> const& c) -> std::map<K, V>;

template <class E, class T>
auto to_map(T const& c, E const& e) -> std::map<typename T::value_type, E>;

template <class E, class T>
auto to_map(T const& c) -> std::map<typename T::value_type, E>;

template <template <class...> class T, class E>
auto is_intersected(T<E> const& lhs, T<E> const& rhs) -> bool;

template <class E>
auto is_intersected(std::set<E> const& lhs, std::set<E> const& rhs) -> bool;

template <class E>
auto is_intersected(std::unordered_set<E> const& lhs,
                    std::unordered_set<E> const& rhs) -> bool;

template <class T>
inline auto is_intersected_set(T const& lhs, T const& rhs) -> bool;

struct Compare {
  template <template <class...> class T, class E,
            class ECompare = std::less<E>>
  auto operator()(T<E> const& lhs, T<E> const& rhs,
                  ECompare const& cmp = ECompare()) const -> bool;

  template <class E, class ECompare = std::less<E>>
  auto operator()(std::unordered_set<E> const& lhs,
                  std::unordered_set<E> const& rhs,
                  ECompare const& cmp = ECompare()) const -> bool;
};
}
}
}

#include "container/container_impl.hpp"
