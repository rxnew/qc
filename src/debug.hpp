#pragma once

#include <iostream>

namespace qc {
namespace debug {
template <template <class...> class T, class... Args>
auto print(T<Args...> const& c, std::ostream& os = std::cout,
           bool line_break = true) -> void;

template <class E>
auto print(E const& e, std::ostream& os = std::cout, bool line_break = true)
  -> void;

template <class K, class V>
auto print(std::pair<K, V> const& p, std::ostream& os = std::cout,
           bool line_break = true) -> void;
}
}

#include "debug/debug_impl.hpp"
