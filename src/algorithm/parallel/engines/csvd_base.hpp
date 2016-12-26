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
inline namespace parallel {
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

  CsvdBase(DependencyGraph const& dependency_graph,
           Predicate predicate = Predicate());
  CsvdBase(DependencyGraph&& dependency_graph,
           Predicate predicate = Predicate());
  virtual ~CsvdBase() = default;

  template <int dim, class Real>
  auto parallelize(Layout<dim, Real> const& layout) -> std::list<Vertices>;

 protected:
  DependencyGraph dependency_graph_;
  DependencyGraph dependency_graph_origin_;
  Predicate predicate_;

  template <int dim, class Real>
  auto _create_graph(Vertices const& vertices, Layout<dim, Real> const& layout)
    const -> Graph;
  template <int dim, class Real>
  auto _create_cliques(Layout<dim, Real> const& layout) const -> Cliques;
  template <int dim, class Real>
  auto _create_group(Layout<dim, Real> const& layout) -> Vertices;
  virtual auto _select_clique(Cliques const& cliques) const
    -> Vertices const& = 0;
};
}
}
}

#include "csvd_base/csvd_base_impl.hpp"
