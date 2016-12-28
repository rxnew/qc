#pragma once

namespace qc {
inline namespace algorithm {
inline namespace parallel {
template <class Overlapped, class Dependency>
template <class... Args>
inline CsvdEv1<Overlapped, Dependency>::CsvdEv1(Args&&... args)
  : Super(std::forward<Args>(args)...) {
}

template <class Overlapped, class Dependency>
inline auto CsvdEv1<Overlapped, Dependency>::
_calculate_evalution_value(Vertices const& clique) const -> int {
  return this->dependency_graph_.count_dependent_vertices(clique);
}

}
}
}
