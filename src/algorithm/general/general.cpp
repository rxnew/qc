/**
 * @file general.cpp
 * @brief implementation of general algorithm
 */

#include "../general.hpp"

#include "../../gate/library/aliases.hpp"

namespace qc {
auto getGateTypeName(const std::string& str) -> const std::string& {
  auto pos = qc::gate_type_aliases.find(str);
  return pos == qc::gate_type_aliases.cend() ? str : pos->second;
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
