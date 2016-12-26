/**
 * @file csvd_base.hpp
 * @brief header of CsvdBase class
 *        Clique consist of the Source vertices of Dependency graph base class
 */

#pragma once

#include "graph/dependency_graph.hpp"
#include "graph/algorithm/bron_kerbosch.hpp"

#include "../../../layout.hpp"
#include "../gate_dependency.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Predicate, class Dependency = GateDependency>
class CsvdBase {
 public:
  using Vertex = std::shared_ptr<Gate>;
  using Graph = graph::UndirectedGraph<Vertex>;
  using Vertices = Graph::Vertices;
  using Cliques = graph::BronKerboschPivot<Graph>::Cliques;
  using DependencyGraph = graph::DependencyGraph<Vertex, Dependency>;
  using predicate = Predicate;
  using dependency = Dependency;

  CsvdBase(DependencyGraph const& dependency_graph);
  CsvdBase(DependencyGraph&& dependency_graph);
  virtual ~CsvdBase() = default;

  template <int dim>
  auto parallelize(Layout<dim> const& layout) -> std::list<Vertices>;

 protected:
  DependencyGraph dependency_graph_;
  DependencyGraph dependency_graph_origin_;

  template <int dim>
  auto _create_graph(Vertices const& vertices, Layout<dim> const& layout) const
    -> Graph;
  template <int dim>
  auto _create_cliques(Layout<dim> const& layout) const -> Cliques;
  template <int dim>
  auto _create_group(Layout<dim> const& layout) -> std::list<Vertices>;
  virtual auto _select_clique(Cliques const& cliques) const
    -> Vertices const& = 0;
};
}
}
}

#include "csvd_base/csvd_base_impl.hpp"
