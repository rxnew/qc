#pragma once

#include <utility>

namespace util {
struct ContainerHelper {
  template <
    template <class...> class U,
    class T>
  static auto convert(const T& c) -> U<typename T::value_type>;
};

template <
  template <class...> class U,
  class T>
inline auto ContainerHelper::convert(const T& c) -> U<typename T::value_type> {
  return std::move(U<typename T::value_type>(c.cbegin(), c.cend()));
}
}
