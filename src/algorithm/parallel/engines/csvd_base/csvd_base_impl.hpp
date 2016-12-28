#pragma once

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Overlapped, class Dependency>
inline CsvdBase<Overlapped, Dependency>::
CsvdBase(DependencyGraph const& dependency_graph, Overlapped overlapped)
  : dependency_graph_origin_(dependency_graph), overlapped_(overlapped) {
}

template <class Overlapped, class Dependency>
inline CsvdBase<Overlapped, Dependency>::
CsvdBase(DependencyGraph&& dependency_graph, Overlapped overlapped)
  : dependency_graph_origin_(std::move(dependency_graph)),
    overlapped_(overlapped) {
}

template <class Overlapped, class Dependency>
template <int dim, class Real>
auto CsvdBase<Overlapped, Dependency>::
parallelize(Layout<dim, Real> const& layout) & -> std::list<Vertices> {
  dependency_graph_ = dependency_graph_origin_;
  return _parallelize(layout);
}

template <class Overlapped, class Dependency>
template <int dim, class Real>
auto CsvdBase<Overlapped, Dependency>::
parallelize(Layout<dim, Real> const& layout) && -> std::list<Vertices> {
  dependency_graph_ = std::move(dependency_graph_origin_);
  return _parallelize(layout);
}

template <class Overlapped, class Dependency>
template <int dim, class Real>
auto CsvdBase<Overlapped, Dependency>::
_parallelize(Layout<dim, Real> const& layout) -> std::list<Vertices> {
  auto groups = std::list<Vertices>();
  while(!dependency_graph_.is_empty()) {
    groups.push_back(_create_group(layout));
  }
  return groups;
}

template <class Overlapped, class Dependency>
template <int dim, class Real>
auto CsvdBase<Overlapped, Dependency>::
_create_graph(Vertices const& vertices, Layout<dim, Real> const& layout) const
  -> Graph {
  auto graph = Graph(vertices);
  for(auto it = vertices.cbegin(); it != vertices.cend(); it++) {
    for(auto jt = it; jt != vertices.cend(); jt++) {
      if(it == jt) continue;
      //if(!overlapped_(**it, **jt, layout)) {
      if(!overlapped_(**it, **jt)) {
        graph.add_edge(*it, *jt);
      }
    }
  }
  return graph;
}

template <class Overlapped, class Dependency>
template <int dim, class Real>
auto CsvdBase<Overlapped, Dependency>::
_create_cliques(Layout<dim, Real> const& layout) const -> Cliques {
  auto const& vertices = dependency_graph_.get_independent_vertices();
  auto graph = _create_graph(vertices, layout);
  return graph::bron_kerbosch_pivot(graph);
}

template <class Overlapped, class Dependency>
template <int dim, class Real>
auto CsvdBase<Overlapped, Dependency>::
_create_group(Layout<dim, Real> const& layout) -> Vertices {
  auto cliques = _create_cliques(layout);
  auto clique = _select_clique(cliques);
  dependency_graph_.remove_vertices(clique);
  return clique;
}
}
}
}
