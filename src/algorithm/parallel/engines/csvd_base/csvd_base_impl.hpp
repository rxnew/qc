#pragma once

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Predicate, class Dependency>
inline CsvdBase<Predicate, Dependency>::
CsvdBase(DependencyGraph const& dependency_graph, Predicate predicate)
  : dependency_graph_origin_(dependency_graph), predicate_(predicate) {
}

template <class Predicate, class Dependency>
inline CsvdBase<Predicate, Dependency>::
CsvdBase(DependencyGraph&& dependency_graph, Predicate predicate)
  : dependency_graph_origin_(std::move(dependency_graph)),
    predicate_(predicate) {
}

template <class Predicate, class Dependency>
template <int dim, class Real>
auto CsvdBase<Predicate, Dependency>::
parallelize(Layout<dim, Real> const& layout)
  -> std::list<Vertices> {
  auto groups = std::list<Vertices>();
  dependency_graph_ = dependency_graph_origin_;
  int i = 0;
  while(!dependency_graph_.is_empty()) {
    groups.push_back(_create_group(layout));
    if(i++ > 1) break;
  }
  return groups;
}

template <class Predicate, class Dependency>
template <int dim, class Real>
auto CsvdBase<Predicate, Dependency>::
_create_graph(Vertices const& vertices, Layout<dim, Real> const& layout) const
  -> Graph {
  auto graph = Graph(vertices);
  for(auto it = vertices.cbegin(); it != vertices.cend(); it++) {
    for(auto jt = it; jt != vertices.cend(); jt++) {
      if(it == jt) continue;
      if(!predicate_(**it, **jt, layout)) {
        graph.add_edge(*it, *jt);
      }
    }
  }
  //std::cout << graph.exist_edge(*vertices.cbegin(), *(++vertices.cbegin())) << std::endl;
  return graph;
}

template <class Predicate, class Dependency>
template <int dim, class Real>
auto CsvdBase<Predicate, Dependency>::
_create_cliques(Layout<dim, Real> const& layout) const -> Cliques {
  auto const& vertices = dependency_graph_.get_independent_vertices();
  auto graph = _create_graph(vertices, layout);
  return graph::bron_kerbosch_pivot(graph);
}

template <class Predicate, class Dependency>
template <int dim, class Real>
auto CsvdBase<Predicate, Dependency>::
_create_group(Layout<dim, Real> const& layout) -> Vertices {
  auto cliques = _create_cliques(layout);
  auto clique = _select_clique(cliques);
  std::cout << cliques.size() << std::endl;
  dependency_graph_.remove_vertices(clique);
  return clique;
}
}
}
}
