/**
 * @file general.cpp
 * @brief implementation of general algorithm
 */

#include "../general.hpp"

#include "../../gate/library/aliases.hpp"

namespace qc {
auto getGateTypeName(const std::string& str) -> const std::string& {
  for(const auto& alias : qc::gate_type_aliases) {
    if(util::string::equalCaseInsensitive(str, alias.second)) {
      return alias.first;
    }
  }
  return str;
}

auto decompIntoSingleTargetGates(const GatePtr& gate) -> GateList {
  const auto& gate_type_name = gate->getTypeName();
  const auto& cbits = gate->getCbitList();
  const auto& tbits = gate->getTbitList();
  GateList result;
  for(const auto& tbit : tbits) {
    result.push_back(createGate(gate_type_name, cbits, tbit));
  }
  return std::move(result);
}

auto decompIntoSingleTargetGates(Circuit& circuit) -> void {
  Circuit result;
  const auto& gates = circuit.getGateList();
  for(const auto& gate : gates) {
    result.insertGate(gates.cend(), qc::decompIntoSingleTargetGates(gate));
  }
  circuit = std::move(result);
}
}
