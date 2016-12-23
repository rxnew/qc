/**
 * @file csvd_ev1.hpp
 * @brief header of CsvdEv1 class
 *        Clique consist of the Source Vertices of Dependency graph
 *        Evaluted Value by number of dependent vertices
 */

#pragma once

#include "csvd_ev_base.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Dependency = GateDependency>
class CsvdEv1 : public CsvdEvBase<Dependency> {
 protected:
  using Super = CsvdEvBase<Dependency>;

 public:
  using Vertex = typename Super::Vertex;
  using Graph = typename Super::Graph;
  using Vertices = typename Super::Vertices;
  using Cliques = typename Super::Cliques;
  using DependencyGraph = typename Super::DependencyGraph;

  template <class... Args>
  CsvdEv1(Args&&... args);
  virtual ~CsvdEv1() = default;

 protected:
  virtual auto calculate_evalution_value(Vertices const& clique) const
    -> int override;
};
}
}
}

#include "csvd_ev1/csvd_ev1_impl.hpp"
