#pragma once

namespace qc {
namespace util {
namespace tmpl {
template <class T, class U = void>
using enable_if_lvalue_t =
  typename std::enable_if_t<std::is_lvalue_reference<T&&>::value, U>;

template <class T, class U = void>
using enable_if_rvalue_t =
  typename std::enable_if_t<std::is_rvalue_reference<T&&>::value, U>;

template <bool Condition, class T = void>
using disable_if = std::enable_if<!Condition, T>;

template <bool Condition, class T = void>
using disable_if_t = typename disable_if<Condition, T>::type;

template <class T>
using remove_qualifier_t =
  typename std::remove_cv_t<typename std::remove_reference_t<T>>;

template <class T, class U>
using is_same_plain =
  std::is_same<remove_qualifier_t<T>, remove_qualifier_t<U>>;

template <class T, class U>
constexpr bool is_same_plain_v = is_same_plain<T, U>::value;

template <class T, class U, class... UArgs>
struct is_same_plain_variadic;

template <class T, class U>
struct is_same_plain_variadic<T, U>;

template <class T, class U, class... UArgs>
constexpr bool is_same_plain_variadic_v =
  is_same_plain_variadic<T, U, UArgs...>::value;

template <class T, class U>
using enable_if_same_t = typename std::enable_if_t<std::is_same<T, U>::value>;

template <class T, class U>
using enable_if_same_plain_t = typename std::enable_if_t<is_same_plain_v<T, U>>;

template <class T, class U>
using enable_if_convertible_t =
  typename std::enable_if_t<std::is_convertible<T, U>::value>;

template <class T>
struct template_class;
 
template <template <class...> class T, class... Args1>
struct template_class<T<Args1...>>;

template <class T, int N = 0>
struct template_parameter;

template <class T, int N = 0>
using template_parameter_t = typename template_parameter<T, N>::type;

template <template <class...> class T, template <class...> class U>
struct is_same_template;

template <template <class...> class T>
struct is_same_template<T, T>;

template <template <class...> class T>
struct is_array_template;

template <template <class...> class T>
struct is_set_template;

template <template <class...> class T>
struct is_map_template;

template <template <class...> class T>
struct is_container_template;

template <class T, class R = remove_qualifier_t<T>>
struct is_array;

template <class T, class R = remove_qualifier_t<T>>
struct is_set;

template <class T, class R = remove_qualifier_t<T>>
struct is_map;

template <class T, class R = remove_qualifier_t<T>>
struct is_container;

template <class T>
constexpr bool is_container_v = is_container<T>::value;

template <class T>
using enable_if_container_t = typename std::enable_if_t<is_container_v<T>>;

// 型Tが型Eを要素とするコンテナかどうか
template <class T, class E>
using enable_if_specified_type_container_t =
  typename std::enable_if_t<is_container_v<T> &&
                            std::is_same<E, typename T::value_type>::value>;
}
}
}

#include "tmpl/tmpl_impl.hpp"
