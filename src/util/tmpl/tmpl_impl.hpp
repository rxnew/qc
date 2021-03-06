#pragma once

#include <vector>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

namespace qc {
namespace util {
namespace tmpl {
template <class T, class U, class... UArgs>
struct is_same_plain_variadic : std::false_type {};

template <class T, class U>
struct is_same_plain_variadic<T, U> : is_same_plain<T, U> {};

template <class T>
struct template_class {};
 
template <template <class...> class T, class... Args1>
struct template_class<T<Args1...>> {
  template <class... Args2>
  using type = T<Args2...>;
};

template <int, class>
struct _template_parameter {};

template <template<class...> class T, class Head, class... Args>
struct _template_parameter<0, T<Head, Args...>> {
  using type = Head;
};

template <int N, template<class...> class T, class Head, class... Args>
struct _template_parameter<N, T< Head, Args... >> {
  using type = typename _template_parameter<N - 1, T<Args...>>::type;
};

template <class T, int N>
struct template_parameter : _template_parameter<N, remove_qualifier_t<T>> {};

template <template <class...> class T, template <class...> class U>
struct is_same_template : std::false_type {};

template <template <class...> class T>
struct is_same_template<T, T> : std::true_type {};

template <template <class...> class T>
struct is_array_template {
  static constexpr bool value =
    is_same_template<T, std::vector>::value ||
    is_same_template<T, std::list>::value   ||
    is_same_template<T, std::deque>::value  ||
    is_same_template<T, std::set>::value    ||
    is_same_template<T, std::unordered_set>::value;
};

template <template <class...> class T>
struct is_set_template {
  static constexpr bool value =
    is_same_template<T, std::set>::value ||
    is_same_template<T, std::unordered_set>::value;
};

template <template <class...> class T>
struct is_map_template {
  static constexpr bool value =
    is_same_template<T, std::map>::value ||
    is_same_template<T, std::unordered_map>::value;
};

template <template <class...> class T>
struct is_container_template {
  static constexpr bool value =
    is_array_template<T>::value || is_map_template<T>::value;
};

template <class E>
struct _is_array {
  static constexpr bool value = false;
};

template <template <class...> class T, class... Args>
struct _is_array<T<Args...>> : is_array_template<T> {};

template <class T, class R>
struct is_array : _is_array<R> {};

template <class E>
struct _is_set {
  static constexpr bool value = false;
};

template <template <class...> class T, class... Args>
struct _is_set<T<Args...>> : is_set_template<T> {};

template <class T, class R>
struct is_set : _is_set<R> {};

template <class E>
struct _is_map {
  static constexpr bool value = false;
};

template <template <class...> class T, class... Args>
struct _is_map<T<Args...>> : is_map_template<T> {};

template <class T, class R>
struct is_map : _is_map<R> {};

template <class E>
struct _is_container {
  static constexpr bool value = false;
};

template <template <class...> class T, class... Args>
struct _is_container<T<Args...>> : is_container_template<T> {};

template <class T, class R>
struct is_container : _is_container<R> {};
}
}
}
