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
inline namespace parallel {
template <class Predicate1 = GateOverlapped, class Predicate2 = GateDependency>
class CsvdEvBase : public CsvdBase<Predicate1, Predicate2> {
 public:
  using Overlapped = Predicate1;
  using Dependency = Predicate2;

 protected:
  using Super = CsvdBase<Overlapped, Dependency>;

 public:
  using Vertex = typename Super::Vertex;
  using Graph = typename Super::Graph;
  using Vertices = typename Super::Vertices;
  using Cliques = typename Super::Cliques;
  using DependencyGraph = typename Super::DependencyGraph;
  using overlapped = Overlapped;
  using dependency = Dependency;

  template <class... Args>
  explicit CsvdEvBase(Args&&... args);
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
