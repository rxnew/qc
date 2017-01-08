#pragma once

#include <iostream>
#include <memory>

#include "mathutils/graph.hpp"

#include "forward_declarations.hpp"
#include "util/tmpl.hpp"

namespace qc {
namespace debug {
template <template <class...> class T, class... Args,
          class = util::tmpl::enable_if_container_t<T<Args...>>>
auto print(T<Args...> const& c, std::ostream& os = std::cout,
           bool line_break = true) -> void;

template <class E>
auto print(E const& e, std::ostream& os = std::cout, bool line_break = true)
  -> void;

template <class E>
auto print(E const* const& e, std::ostream& os = std::cout, bool line_break = true)
  -> void;

template <class E>
auto print(std::unique_ptr<E> const& e, std::ostream& os = std::cout,
           bool line_break = true) -> void;

template <class E>
auto print(std::shared_ptr<E> const& e, std::ostream& os = std::cout,
           bool line_break = true) -> void;

template <class E>
auto print(std::weak_ptr<E> const& e, std::ostream& os = std::cout,
           bool line_break = true) -> void;

template <class K, class V>
auto print(std::pair<K, V> const& p, std::ostream& os = std::cout,
           bool line_break = true) -> void;

auto print_graph(mathutils::Graph<std::shared_ptr<Gate>> const& g,
                 std::ostream& os = std::cout) -> void;
}
}

#include "debug/debug_impl.hpp"
