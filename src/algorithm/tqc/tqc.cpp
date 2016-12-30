#include "../tqc.hpp"

#include "../../gate/library/x.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
auto combine_cnot_into_mtc(Gate const& gate) -> Gate {
  if(!gate.is_group()) return gate;
  auto combined_group = make_group();
  auto mtcs = std::unordered_map<CBit, X>();
  for(auto const& gate : gate.get_gates()) {
    if(is_cnot(gate, true)) mtcs[get_cbit(gate)].add_tbit(gate.get_tbits());
    else                    combined_group.add_gate(gate);
  }
  for(auto& e : mtcs) {
    auto const& cbit = e.first;
    auto& mtc = e.second;
    mtc.add_cbit(cbit);
    combined_group.add_gate(std::move(mtc));
  }
  return combined_group;
}

auto combine_cnot_into_mtc(Circuit const& circuit) -> Circuit {
  auto combined_circuit = Circuit();
  for(auto const& gate : circuit.get_gates()) {
    combined_circuit.add_gate(combine_cnot_into_mtc(gate));
  }
  return combined_circuit;
}
}
}
}
