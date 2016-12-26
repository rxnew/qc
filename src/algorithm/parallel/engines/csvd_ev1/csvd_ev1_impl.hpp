#pragma once

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Predicate, class Dependency>
template <class... Args>
inline CsvdEv1<Predicate, Dependency>::CsvdEv1(Args&&... args)
  : Super(std::forward<Args>(args)...) {
}

template <class Predicate, class Dependency>
inline auto CsvdEv1<Predicate, Dependency>::
_calculate_evalution_value(Vertices const& clique) const -> int {
  return this->dependency_graph_.count_dependent_vertices(clique);
}

}
}
}
