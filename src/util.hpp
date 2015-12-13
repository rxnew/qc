#pragma once

#include <set>
#include <unordered_set>

namespace util {
template <class T>
std::set<T> getOrderedContainer(const std::unordered_set<T>& container);
}
