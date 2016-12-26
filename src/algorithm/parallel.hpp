#pragma once

#include "graph/dependency_graph.hpp"

#include "../circuit.hpp"
#include "parallel/engines/csvd_ev1.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <int dim, class Engine>
auto parallelize(Circuit const& circuit, Layout<dim> const& layout) -> Circuit;
template <class Dependency = GateDependency>
auto create_dependency_graph(Circuit circuit)
  -> graph::DependencyGraph<std::shared_ptr<Gate>, Dependency>;
}
}
}
