#pragma once

#include "../group.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Engine, int dim, class Real>
auto parallelize(Circuit const& circuit, Layout<dim, Real> const& layout)
  -> Circuit {
  using dependency = typename Engine::dependency;

  auto parallelized_circuit = Circuit();
  auto engine = Engine(create_dependency_graph<dependency>(circuit));
  auto cliques = engine.parallelize(layout);

  for(auto& vertices : cliques) {
    auto group = Group();
    for(auto& v : vertices) {
      group.add_gate(std::move(*v));
    }
    parallelized_circuit.add_gate(std::move(group));
  }

  return parallelized_circuit;
}

template <class Dependency>
auto create_dependency_graph(Circuit circuit)
  -> graph::DependencyGraph<std::shared_ptr<Gate>, Dependency> {
  auto graph = graph::DependencyGraph<std::shared_ptr<Gate>, Dependency>();
  expand_groups(circuit);
  auto f = [&graph](Gates& gates) {
    for(auto& gate : gates) {
      graph.add_vertex(std::make_shared<Gate>(std::move(gate)));
    }
  };
  circuit.apply_to_gates(f);
  return graph;
}
}
}
}