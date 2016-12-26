/**
 * @file set.hpp
 * @brief header of utilities of set
 */

#pragma once

#include <unordered_set>

namespace qc {
namespace util {
namespace set {
template <class T>
auto set_union(std::unordered_set<T> const& set, const T& value)
  -> std::unordered_set<T>;

template <class T>
auto set_union(std::unordered_set<T> const& lhs,
               std::unordered_set<T> const& rhs)
  -> std::unordered_set<T>;

template <class T>
auto set_intersection(std::unordered_set<T> const& lhs,
                      std::unordered_set<T> const& rhs)
  -> std::unordered_set<T>;

template <class T>
auto set_difference(std::unordered_set<T> const& lhs,
                    std::unordered_set<T> const& rhs)
  -> std::unordered_set<T>;

template <class T>
auto is_intersected(std::unordered_set<T> const& lhs,
                    std::unordered_set<T> const& rhs) -> bool;
}
}
}

#include "set/set_impl.hpp"
