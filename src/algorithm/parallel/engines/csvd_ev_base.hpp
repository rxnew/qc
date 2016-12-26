/**
 * @file csvd_ev_base.hpp
 * @brief header of CsvdEvBase class
 *        Clique consist of the Source vertices of Dependency graph
 *        Evaluted Value base class
 */

#pragma once

#include "csvd_base.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Predicate, class Dependency = GateDependency>
class CsvdEvBase : public CsvdBase<Predicate, Dependency> {
 protected:
  using Super = CsvdBase<Predicate, Dependency>;

 public:
  using Vertex = typename Super::Vertex;
  using Graph = typename Super::Graph;
  using Vertices = typename Super::Vertices;
  using Cliques = typename Super::Cliques;
  using DependencyGraph = typename Super::DependencyGraph;
  using predicate = Predicate;
  using dependency = Dependency;

  template <class... Args>
  CsvdEvBase(Args&&... args);
  virtual ~CsvdEvBase() = default;

 protected:
  virtual auto _select_clique(Cliques const& cliques) const
    -> Vertices const& override;
  virtual auto _calculate_evalution_value(Vertices const& clique) const
    -> int = 0;
};
}
}
}

#include "csvd_ev_base/csvd_ev_base_impl.hpp"
