#pragma once

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Predicate, class Dependency>
inline CsvdBase<Predicate, Dependency>::
CsvdBase(DependencyGraph const& dependency_graph)
  : dependency_graph_origin_(dependency_graph) {
}

template <class Predicate, class Dependency>
inline CsvdBase<Predicate, Dependency>::
CsvdBase(DependencyGraph&& dependency_graph)
  : dependency_graph_origin_(std::move(dependency_graph)) {
}

template <class Predicate, class Dependency>
template <int dim>
auto CsvdBase<Predicate, Dependency>::
parallelize(Layout<dim> const& layout)
  -> std::list<Vertices> {
  auto groups = std::list<Vertices>();
  dependency_graph_ = dependency_graph_origin_;
  while(!dependency_graph_.is_empty()) {
    groups.push_back(create_group(layout));
  }
  return groups;
}

template <class Predicate, class Dependency>
template <int dim>
auto CsvdBase<Predicate, Dependency>::
_create_graph(Vertices const& vertices, Layout<dim> const& layout) const
  -> Graph {
  auto graph = Graph(vertices);
  for(auto it = vertices.cbegin(); it != vertices.cend(); it++) {
    for(auto jt = it; jt != vertices.cend(); jt++) {
      if(it == jt) continue;
      if(!Predicate(*it, *jt, layout)) {
        graph.add_edge(*it, *jt);
      }
    }
  }
  return graph;
}

template <class Predicate, class Dependency>
template <int dim>
auto CsvdBase<Predicate, Dependency>::
_create_cliques(Layout<dim> const& layout) const -> Cliques {
  auto const& vertices = dependency_graph_.get_independent_vertices();
  auto graph = _create_non_overlapped_graph(vertices, layout);
  return graph::bron_kerbosch_pivot(graph);
}

template <class Predicate, class Dependency>
template <int dim>
auto CsvdBase<Predicate, Dependency>::
_create_group(Layout<dim> const& layout) -> std::list<Vertices> {
  auto cliques = _create_cliques(layout);
  dependency_graph_.remove_vertex(cliques);
  return _select_clique(cliques);
}
}
}
}
