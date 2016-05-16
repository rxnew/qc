#pragma once

namespace qc {
namespace util {
namespace tmpl {
template <class T>
struct template_class;
 
template <template <class...> class T, class... Args1>
struct template_class<T<Args1...>>;

template <template <class...> class T, template <class...> class U>
struct is_same_template;

template <template <class...> class T>
struct is_same_template<T, T>;

template <template <class...> class T>
struct is_array_template;

template <template <class...> class T>
struct is_object_template;

template <template <class...> class T>
struct is_container_template;

template <class E>
struct is_array;

template <template <class...> class T, class... Args>
struct is_array<T<Args...>>;

template <class E>
struct is_map;

template <template <class...> class T, class... Args>
struct is_map<T<Args...>>;

template <class E>
struct is_container;

template <template <class...> class T, class... Args>
struct is_container<T<Args...>>;
}
}
}

#include "tmpl/tmpl_impl.hpp"
