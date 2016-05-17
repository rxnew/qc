/**
 * @file oracle.hpp
 * @brief header of algorithm for quantum oracle
 */

#pragma once

#include "../circuit.hpp"

namespace qc {
auto collectCbits(const Circuit& circuit) -> BitList;
auto collectTbits(const Circuit& circuit) -> BitList;
auto isMctCircuit(const Circuit& circuit) -> bool;
template <class GatePtrT>
auto getMctCost(const GatePtrT& gate) -> int;
auto calcMctCircuitCost(const Circuit& circuit) -> int;
auto sortGatesByCbits(Circuit& circuit) -> void;
auto sortGatesByTbits(Circuit& circuit) -> void;
auto sortGates(Circuit& circuit) -> void;
auto decompIntoSingleTargetCircuits(const Circuit& circuit)
  -> std::unordered_map<Tbit, Circuit>;
}

#include "oracle/oracle_impl.hpp"
