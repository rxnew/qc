#pragma once

#include "parallel.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Engine>
auto parallelize(Circuit const& circuit, Layout const& layout) -> Circuit {
  auto parallelized_circuit = Circuit();
  auto cliques = Engine(create_dependency_graph(circuit)).parallelize(layout);
  for(auto& vertices : cliques) {
    auto group = Group();
    for(auto& v : vertices) {
      group.add_gate(std::move(*v));
    }
    parallelized_circuit.add_gate(std::move(group));
  }
  return parallelized_circuit;
}
}
}
}
