#pragma once

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Dependency>
template <class... Args>
inline CsvdEvBase<Dependency>::CsvdEvBase(Args&&... args)
  : Super(std::forward<Args>(args)...) {
}

template <class Dependency>
auto CsvdEvBase<Dependency>::_select_clique(Cliques const& cliques) const
  -> const Vertices& {
  assert(!cliques.empty());

  auto result = cliques.cbegin();
  auto max_evalution_value = _calculate_evalution_value(*it);
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
