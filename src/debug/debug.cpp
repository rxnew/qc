#include "../debug.hpp"

#include "../gate.hpp"

namespace qc {
namespace debug {
auto print_graph(mathutils::Graph<std::shared_ptr<Gate>> const& g, std::ostream& os)
  -> void {
  for(auto const& v : g.get_vertices()) {
    os << *v << ": {";
    auto first = true;
    for(auto const& u : g.get_neighbors(v)) {
      if(!first) os << ", ";
      else first = false;
      os << *u;
    }
    os << "}" << std::endl;
  }
}
}
}
