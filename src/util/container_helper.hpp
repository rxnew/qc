#pragma once

#include <vector>
#include <list>
#include <set>
#include <unordered_set>

namespace util {
struct ContainerConverter {
  template <class T, class U = typename T::value_type>
  static inline auto to_vector(const T& c) \
    -> std::vector<U> {
    return std::move(std::vector<U>(c.cbegin(), c.cend()));
  }

  template <class T, class U = typename T::value_type>
  static inline auto to_list(const T& c) \
    -> std::list<U> {
    return std::move(std::list<U>(c.cbegin(), c.cend()));
  }

  template <class T, class U = typename T::value_type>
  static inline auto to_set(const T& c) \
    -> std::set<U> {
    return std::move(std::set<U>(c.cbegin(), c.cend()));
  }

  template <class T, class U = typename T::value_type>
  static inline auto to_unordered_set(const T& c) \
    -> std::unordered_set<U> {
    return std::move(std::unordered_set<U>(c.cbegin(), c.cend()));
  }
};
}
