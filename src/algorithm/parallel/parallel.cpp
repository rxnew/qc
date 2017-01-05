#include "../parallel.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
auto make_circuit(CsvdBase<>::Cliques const& cliques) -> Circuit {
  return make_circuit(decltype(cliques)(cliques));
}

auto make_circuit(CsvdBase<>::Cliques&& cliques) -> Circuit {
  auto circuit = Circuit();
  for(auto& vertices : cliques) {
    auto group = Group();
    for(auto& v : vertices) {
      group.add_gate(std::move(*v));
    }
    circuit.add_gate(std::move(group));
  }
  return circuit;
}
}
}
}
