#pragma once

#include "graph/dependency_graph.hpp"

#include "../../circuit.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Dependency>
auto create_dependency_graph(Circuit const& circuit)
  -> graph::DependencyGraph<std::shared_ptr<Gate>, Dependency>;
}
}
}
