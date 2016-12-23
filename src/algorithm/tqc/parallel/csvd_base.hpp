/**
 * @file csvd_base.hpp
 * @brief header of CsvdBase class
 *        Clique consist of the Source vertices of Dependency graph base class
 */

#pragma once

#include "graph/dependency_graph.hpp"
#include "graph/algorithm/bron_kerbosch.hpp"

#include "gate_dependency.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Dependency = GateDependency>
class CsvdBase {
 public:
  using Vertex = std::shared_ptr<Gate>;
  using Graph = graph::UndirectedGraph<Vertex>;
  using Vertices = Graph::Vertices;
  using Cliques = graph::BronKerboschPivot<Graph>::Cliques;
  using DependencyGraph = graph::DependencyGraph<Vertex, Dependency>;

  CsvdBase(DependencyGraph const& dependency_graph);
  CsvdBase(DependencyGraph&& dependency_graph);
  virtual ~CsvdBase() = default;

  auto parallelize(Layout const& layout) -> std::list<Vertices>;

 protected:
  DependencyGraph dependency_graph_;
  DependencyGraph dependency_graph_origin_;

  virtual auto _create_non_overlapped_graph(Vertices const& vertices,
                                            Layout const& layout) const
    -> Graph;
  virtual auto _create_cliques(Layout const& layout) const -> Cliques;
  virtual auto _select_clique(Cliques const& cliques) const
    -> Vertices const& = 0;
  virtual auto _create_group(Layout const& layout) -> std::list<Vertices>;
};
}
}
}

#include "csvd_base/csvd_base_impl.hpp"
