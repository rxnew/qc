#pragma once

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Predicate, class Dependency>
template <class... Args>
inline CsvdEvBase<Predicate, Dependency>::CsvdEvBase(Args&&... args)
  : Super(std::forward<Args>(args)...) {
}

template <class Predicate, class Dependency>
auto CsvdEvBase<Predicate, Dependency>::
_select_clique(Cliques const& cliques) const -> const Vertices& {
  assert(!cliques.empty());

  auto result = cliques.cbegin();
  auto max_evalution_value = _calculate_evalution_value(*result);
  for(auto it = ++cliques.cbegin(); it != cliques.cend(); it++) {
    auto evalution_value = _calculate_evalution_value(*it);
    if(evalution_value > max_evalution_value) {
      max_evalution_value = evalution_value;
      result = it;
    }
  }
  return *result;
}
}
}
}
