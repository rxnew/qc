#pragma once

#include "graph/dependency_graph.hpp"

#include "parallel/engines.hpp"
#include "../circuit.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Engine, int dim, class Real,
          class Overlapped = typename Engine::Overlapped>
auto parallelize(Circuit const& circuit, Layout<dim, Real> const& layout,
                 Overlapped overlapped = Overlapped()) -> Circuit;
template <class Dependency = GateDependency>
auto create_dependency_graph(Circuit circuit)
  -> graph::DependencyGraph<std::shared_ptr<Gate>, Dependency>;
}
}
}

#include "parallel/parallel_impl.hpp"
