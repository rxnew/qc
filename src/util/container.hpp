#pragma once

#include <map>

namespace qc {
namespace util {
namespace container {
template <template <class...> class U, class T>
constexpr auto convert(const T& c) -> U<typename T::value_type>;

template <template <class...> class U, class T>
constexpr auto convertMap(const T& c)
  -> U<typename T::key_type, typename T::mapped_type>;

template <class E, class T>
auto toMap(const T& c, const E& e)
  -> std::map<typename T::value_type, E>;

template <class E, class T>
auto toMap(const T& c) -> std::map<typename T::value_type, E>;
}
}
}

#include "container/container_impl.hpp"
