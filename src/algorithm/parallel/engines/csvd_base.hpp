/**
 * @file csvd_base.hpp
 * @brief header of CsvdBase class
 *        Clique consist of the Source vertices of Dependency graph base class
 */

#pragma once

#include "graph/dependency_graph.hpp"
#include "graph/algorithm/bron_kerbosch.hpp"

#include "../predicates.hpp"

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Predicate1 = GateOverlapped, class Predicate2 = GateDependency>
class CsvdBase {
 public:
  using Overlapped = Predicate1;
  using Dependency = Predicate2;
  using Vertex = std::shared_ptr<Gate>;
  using Graph = graph::UndirectedGraph<Vertex>;
  using Vertices = Graph::Vertices;
  using Cliques = graph::BronKerboschPivot<Graph>::Cliques;
  using DependencyGraph = graph::DependencyGraph<Vertex, Dependency>;

  explicit CsvdBase(DependencyGraph const& dependency_graph,
                    Overlapped overlapped = Overlapped());
  explicit CsvdBase(DependencyGraph&& dependency_graph,
                    Overlapped overlapped = Overlapped());
  virtual ~CsvdBase() = default;

  auto parallelize() & -> std::list<Vertices>;
  auto parallelize() && -> std::list<Vertices>;

 protected:
  DependencyGraph dependency_graph_;
  DependencyGraph const dependency_graph_origin_;
  Overlapped overlapped_;

  auto _parallelize() -> std::list<Vertices>;
  auto _create_group() -> Vertices;
  auto _create_cliques() const -> Cliques;
  auto _create_graph(Vertices const& vertices) const -> Graph;
  virtual auto _select_clique(Cliques const& cliques) const
    -> Vertices const& = 0;
};
}
}
}

#include "csvd_base/csvd_base_impl.hpp"
