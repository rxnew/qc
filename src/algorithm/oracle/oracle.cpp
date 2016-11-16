/**
 * @file oracle.cpp
 * @brief implementation of algorithm for quantum oracle
 */

#include "../oracle.hpp"

#include "../general.hpp"
#include "../../gate/library/x.hpp"
#include "../../circuit.hpp"
#include "../../util/container.hpp"
#include "../../util/math.hpp"

namespace qc {
auto collect_cbits(Gate const& gate) -> BitNos {
  auto bit_nos = BitNos();
  for(auto const& cbit : gate.get_cbits()) {
    bit_nos.insert(cbit.get_no());
  }
  return bit_nos;
}

auto collect_cbits(Circuit const& circuit) -> BitNos {
  auto bit_nos = BitNos();
  for(auto const& gate : circuit.get_gates()) {
    for(auto const& cbit : gate.get_cbits()) {
      bit_nos.insert(cbit.get_no());
    }
  }
  return bit_nos;
}

auto collect_tbits(Gate const& gate) -> BitNos {
  auto bit_nos = BitNos();
  for(auto const& tbit : gate.get_tbits()) {
    bit_nos.insert(tbit.get_no());
  }
  return bit_nos;
}

auto collect_tbits(Circuit const& circuit) -> BitNos {
  auto bit_nos = BitNos();
  for(auto const& gate : circuit.get_gates()) {
    for(auto const& tbit : gate.get_tbits()) {
      bit_nos.insert(tbit.get_no());
    }
  }
  return bit_nos;
}

auto is_mct_circuit(Circuit const& circuit) -> bool {
  for(auto const& gate : circuit.get_gates()) {
    if(gate.get_type_name() != X::TYPE_NAME) return false;
  }
  return true;
}

auto is_esop_circuit(Circuit const& circuit) -> bool {
  auto const cbit_nos = collect_cbits(circuit);
  auto const tbit_nos = collect_tbits(circuit);
  return !util::container::is_intersected(cbit_nos, tbit_nos)
    && cbit_nos.size() + tbit_nos.size() == circuit.collect_bits().size()
    && is_mct_circuit(circuit);
}

auto get_mct_cost(Gate const& gate, bool decomp_flag) -> unsigned long long {
  assert(gate.get_type_name() == X::TYPE_NAME);

  // Please refer to arXiv:quant-ph/0403053
  static constexpr std::array<unsigned long long, 11> const C = {
    1, 1, 5, 13, 29, 61, 52, 125, 253, 509, 1021
  };

  auto size = gate.get_cbits().size();
  auto n = static_cast<unsigned long long>(gate.get_tbits().size());
  auto cost_s = (size < C.size() ? C[size] : util::math::pow(2ull, size) - 3);
  return decomp_flag ? cost_s + (n << 1) : cost_s * n;
}

auto calculate_mct_circuit_cost(Circuit const& circuit, bool decomp_flag)
  -> unsigned long long {
  auto total_cost = 0ull;
  for(auto const& gate : circuit.get_gates()) {
    total_cost += get_mct_cost(gate, decomp_flag);
  }
  return total_cost;
}

auto sort_gates_by_cbits(Circuit& circuit) -> void {
  auto const g = [](CBit const& lhs, CBit const& rhs) {
    return Bit(lhs) < Bit(rhs);
  };
  auto const f = [&g](Gate const& lhs, Gate const& rhs) {
    return util::container::Compare()(lhs.get_cbits(), rhs.get_cbits(), g);
  };
  auto gates = circuit.get_gates();
  gates.sort(f);
  circuit.set_gates(std::move(gates));
}

auto sort_gates_by_tbits(Circuit& circuit) -> void {
  const auto f = [](Gate const& lhs, Gate const& rhs) {
    return util::container::Compare()(lhs.get_tbits(), rhs.get_tbits());
  };
  auto gates = circuit.get_gates();
  gates.sort(f);
  circuit.set_gates(std::move(gates));
}

auto sort_gates(Circuit& circuit) -> void {
  sort_gates_by_cbits(circuit);
  sort_gates_by_tbits(circuit);
}

auto decomp_to_single_target_circuits(Circuit const& circuit)
  -> std::unordered_map<TBit, Circuit> {
  auto result_circuit = std::unordered_map<TBit, Circuit>();
  for(auto const& gate : circuit.get_gates()) {
    for(auto const& decomposed_gate : decomp_to_single_target_gates(gate)) {
      result_circuit[get_tbit(decomposed_gate)].add_gate(decomposed_gate);
    }
  }
  return result_circuit;
}
}
