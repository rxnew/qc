#include "util.hpp"

namespace util {
template <class T>
std::set<T> getOrderedContainer(const std::unordered_set<T>& container) {
  std::set<T> ordered_container;
  for(const auto& element : container)
    ordered_container.insert(element);
  return std::move(ordered_container);
}
}
