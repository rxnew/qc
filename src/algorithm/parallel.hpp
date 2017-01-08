#pragma once

#include "mathutils/graph.hpp"

#include "parallel/engines.hpp"
#include "../forward_declarations.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Engine, class Overlapped = typename Engine::Overlapped>
auto parallelize(Circuit const& circuit, Overlapped overlapped = Overlapped())
  -> Circuit;
template <class Dependency = GateDependency>
auto make_dependency_graph(Circuit circuit)
  -> mathutils::DependencyGraph<std::shared_ptr<Gate>, Dependency>;
auto make_circuit(CsvdBase<>::Cliques const& cliques) -> Circuit;
auto make_circuit(CsvdBase<>::Cliques&& cliques) -> Circuit;
}
}
}

#include "parallel/parallel_impl.hpp"
