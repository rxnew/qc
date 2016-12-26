#pragma once

#include "graph/dependency_graph.hpp"

#include "../circuit.hpp"
#include "parallel/engines/csvd_ev1.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Engine, int dim, class Real>
auto parallelize(Circuit const& circuit, Layout<dim, Real> const& layout)
  -> Circuit;
template <class Dependency = GateDependency>
auto create_dependency_graph(Circuit circuit)
  -> graph::DependencyGraph<std::shared_ptr<Gate>, Dependency>;
}
}
}

#include "parallel/parallel_impl.hpp"
