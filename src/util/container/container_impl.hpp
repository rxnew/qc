#pragma once

namespace qc {
namespace util {
namespace container {
template <template <class...> class U, class T>
inline constexpr auto convert(const T& c) -> U<typename T::value_type> {
  return std::move(U<typename T::value_type>(c.cbegin(), c.cend()));
}

template <template <class...> class U, class T>
inline constexpr auto convertMap(const T& c)
  -> U<typename T::key_type, typename T::mapped_type> {
  return std::move(
    U<typename T::key_type, typename T::mapped_type>(c.cbegin(), c.cend()));
}

template <class E, class T>
auto toMap(const T& c, const E& e)
  -> std::map<typename T::value_type, E> {
  std::map<typename T::value_type, E> m;
  for(const auto& k : c) {
    m.insert(std::make_pair(k, e));
  }
  return std::move(m);
}

template <class E, class T>
inline auto toMap(const T& c) -> std::map<typename T::value_type, E> {
  return toMap(c, E());
}
}
}
}
