#pragma once

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Dependency>
inline CsvdBase<Dependency>::CsvdBase(DependencyGraph const& dependency_graph)
  : dependency_graph_origin_(dependency_graph) {
}

template <class Dependency>
inline CsvdBase<Dependency>::CsvdBase(DependencyGraph&& dependency_graph)
  : dependency_graph_origin_(std::move(dependency_graph)) {
}

template <class Dependency>
auto CsvdBase<Dependency>::parallelize(const Layout& layout)
  -> std::list<Vertices> {
  auto groups = std::list<Vertices>();
  dependency_graph_ = dependency_graph_origin_;
  while(!dependency_graph_.is_empty()) {
    groups.push_back(create_group(layout));
  }
  return groups;
}

template <class Dependency>
auto CsvdBase<Dependency>::
_create_non_overlapped_graph(Vertices const& vertices,
                             Layout const& layout) const -> Graph {
  auto graph = Graph(vertices);
  for(auto it = vertices.cbegin(); it != vertices.cend(); it++) {
    for(auto jt = it; jt != vertices.cend(); jt++) {
      if(it == jt) continue;
      if(!is_overlapped(*it, *jt, layout, allow_mtc)) {
        graph.add_edge(*it, *jt);
      }
    }
  }
  return graph;
}

template <class Dependency>
auto CsvdBase<Dependency>::_create_cliques(Layout const& layout) const
  -> Cliques {
  auto const& vertices = dependency_graph_.get_independent_vertices();
  auto graph = _create_non_overlapped_graph(vertices, layout);
  return graph::bron_kerbosch_pivot(graph);
}

template <class Dependency>
auto CsvdBase<Dependency>::_create_group(Layout const& layout) -> Group {
  auto cliques = _create_cliques(layout);
  dependency_graph_.remove_vertex(cliques);
  return _select_clique(cliques);
}
}
}
}
