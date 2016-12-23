#pragma once

namespace qc {
namespace util {
inline namespace set {
template <class T>
auto set_union(std::unordered_set<T> const& set, T const& value)
  -> std::unordered_set<T> {
  std::unordered_set<T> result = set;
  result.insert(value);
  return result;
}

template <class T>
auto set_union(std::unordered_set<T> const& lhs,
               std::unordered_set<T> const& rhs)
  -> std::unordered_set<T> {
  std::unordered_set<T> result;
  for(auto const& x : lhs) {
    result.insert(x);
  }
  for(auto const& x : rhs) {
    result.insert(x);
  }
  return result;
}

template <class T>
auto set_intersection(std::unordered_set<T> const& lhs,
                      std::unordered_set<T> const& rhs)
  -> std::unordered_set<T> {
  std::unordered_set<T> result;
  for(auto const& x : lhs) {
    if(rhs.find(x) != rhs.cend()) result.insert(x);
  }
  return result;
}

template <class T>
auto set_difference(std::unordered_set<T> const& lhs,
                    std::unordered_set<T> const& rhs)
  -> std::unordered_set<T> {
  std::unordered_set<T> result;
  for(auto const& x : lhs) {
    if(rhs.find(x) == rhs.cend()) result.insert(x);
  }
  return result;
}

template <class T>
auto is_intersected(std::unordered_set<T> const& lhs,
                    std::unordered_set<T> const& rhs) -> bool {
  for(auto const& x : lhs) {
    if(rhs.find(x) != rhs.cend()) return true;
  }
  return false;
}
}
}
}
