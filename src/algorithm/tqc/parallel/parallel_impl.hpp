#pragma once

#include "../../group.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
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
