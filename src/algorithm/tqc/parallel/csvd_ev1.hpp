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
  using Vertex = Super::Vertex;
  using Graph = Super::Graph;
  using Vertices = Super::Vertices;
  using Cliques = Super::Cliques;
  using DependencyGraph = Super::DependencyGraph;

  template <class... Args>
  CsvdEv1(Args&&... args);
  virtual ~CsvdEv1() = default;

 protected:
  virtual auto calculate_evalution_value(Vertices const& clique) const override
    -> int;
};
}
}
}

#include "csvd_ev1/csvd_ev1_impl.hpp"
