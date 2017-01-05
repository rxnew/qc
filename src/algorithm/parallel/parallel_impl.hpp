#pragma once

#include "../../circuit.hpp"
#include "../../gate/group.hpp"
#include "../group.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Engine, class Overlapped>
auto parallelize(Circuit const& circuit, Overlapped overlapped) -> Circuit {
  using Dependency = typename Engine::Dependency;
  auto dependency_graph = make_dependency_graph<Dependency>(circuit);
  auto engine = Engine(std::move(dependency_graph), overlapped);
  auto cliques = std::move(engine).parallelize();
  return make_circuit(std::move(cliques));
}

template <class Dependency>
auto make_dependency_graph(Circuit circuit)
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
