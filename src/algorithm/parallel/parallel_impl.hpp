#pragma once

#include "../../group.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <int dim, class Engine>
auto parallelize(Circuit const& circuit, Layout<dim> const& layout) -> Circuit {
  auto parallelized_circuit = Circuit();
  auto engine = Engine(create_dependency_graph<Engine::dependency>(circuit));
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
