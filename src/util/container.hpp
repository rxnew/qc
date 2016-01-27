#pragma once

#include <utility>

namespace util {
namespace container {
template <
  template <class...> class U,
  class T>
inline constexpr auto convert(const T& c) -> U<typename T::value_type> {
  return std::move(U<typename T::value_type>(c.cbegin(), c.cend()));
}
}
}
