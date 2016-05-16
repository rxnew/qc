#pragma once

#include <iostream>

namespace qc {
namespace debug {
template <template <class...> class T, class... Args>
auto print(const T<Args...>& c, std::ostream& os = std::cout,
           bool line_break = true) -> void;

template <class E>
auto print(const E& e, std::ostream& os = std::cout,
           bool line_break = true) -> void;

template <class K, class V>
auto print(const std::pair<K, V>& p, std::ostream& os = std::cout,
           bool line_break = true) -> void;
}
}

#include "debug/debug_impl.hpp"
