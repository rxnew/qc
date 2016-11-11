/**
 * @file oracle.cpp
 * @brief implementation of algorithm for quantum oracle
 */

#include "../oracle.hpp"

#include "../general.hpp"

namespace qc {
auto collectCbits(const Gate& gate) -> BitList {
  BitList bits;
  for(const auto& cbit : gate.getCbitList()) {
    bits.insert(cbit.bitno_);
  }
  return std::move(bits);
}

auto collectCbits(const Circuit& circuit) -> BitList {
  BitList bits;
  for(const auto& gate : circuit.getGateList()) {
    for(const auto& cbit : gate->getCbitList()) {
      bits.insert(cbit.bitno_);
    }
  }
  return std::move(bits);
}

auto collectTbits(const Gate& gate) -> BitList {
  BitList bits;
  for(const auto& tbit : gate.getTbitList()) {
    bits.insert(tbit.bitno_);
  }
  return std::move(bits);
}

auto collectTbits(const Circuit& circuit) -> BitList {
  BitList bits;
  for(const auto& gate : circuit.getGateList()) {
    for(const auto& tbit : gate->getTbitList()) {
      bits.insert(tbit.bitno_);
    }
  }
  return std::move(bits);
}

auto isMctCircuit(const Circuit& circuit) -> bool {
  for(const auto& gate : circuit.getGateList()) {
    if(gate->getTypeName() != X::TYPE_NAME) return false;
  }
  return true;
}

auto isEsopCircuit(const Circuit& circuit) -> bool {
  const auto cbits_no = qc::collectCbits(circuit);
  const auto tbits_no = qc::collectTbits(circuit);
  return !util::container::isIntersected(cbits_no, tbits_no)
    && cbits_no.size() + tbits_no.size() == circuit.collectUsedBits().size()
    && qc::isMctCircuit(circuit);
}

auto getMctCost(const Gate& gate, bool decomp) -> unsigned long long {
  assert(gate.getTypeName() == X::TYPE_NAME);

  // Please refer to arXiv:quant-ph/0403053
  static constexpr std::array<unsigned long long, 11> C = {
    1, 1, 5, 13, 29, 61, 52, 125, 253, 509, 1021
  };

  auto size = gate.getCbitList().size();
  auto n = static_cast<unsigned long long>(gate.getTbitList().size());
  auto cost_s = (size < C.size() ? C[size] : util::math::pow(2ull, size) - 3);
  return decomp ? cost_s + n * 2 : cost_s * n;
}

auto calcMctCircuitCost(const Circuit& circuit,
                        bool decomp) -> unsigned long long {
  auto total_cost = 0ull;
  for(const auto& gate : circuit.getGateList()) {
    total_cost += qc::getMctCost(*gate, decomp);
  }
  return total_cost;
}

auto sortGatesByCbits(Circuit& circuit) -> void {
  const auto f = [](const GatePtr& lhs, const GatePtr& rhs) {
    return util::container::Compare()(lhs->getCbitList(), rhs->getCbitList(),
                                      [](const Cbit& lhs, const Cbit& rhs) {
                                        return Bit(lhs) < Bit(rhs);});
  };
  circuit.getGateList().sort(f);
}

auto sortGatesByTbits(Circuit& circuit) -> void {
  const auto f = [](const GatePtr& lhs, const GatePtr& rhs) {
    return util::container::Compare()(lhs->getTbitList(), rhs->getTbitList());
  };
  circuit.getGateList().sort(f);
}

auto sortGates(Circuit& circuit) -> void {
  qc::sortGatesByCbits(circuit);
  qc::sortGatesByTbits(circuit);
}

auto decompIntoSingleTargetCircuits(const Circuit& circuit)
  -> std::unordered_map<Tbit, Circuit> {
  std::unordered_map<Tbit, Circuit> result;
  for(const auto& gate : circuit.getGateList()) {
    for(const auto& gate_s : qc::decompIntoSingleTargetGates(gate)) {
      result[qc::getTbit(gate_s)].addGate(gate_s->clone());
    }
  }
  return std::move(result);
}
}
