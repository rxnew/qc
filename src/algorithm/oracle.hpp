/**
 * @file oracle.hpp
 * @brief header of algorithm for quantum oracle
 */

#pragma once

#include "../circuit.hpp"

namespace qc {
auto collectCbits(const Gate& gate) -> BitList;
template <class GatePtrT>
auto collectCbits(const GatePtrT& gate) -> BitList;
auto collectCbits(const Circuit& circuit) -> BitList;
auto collectTbits(const Gate& gate) -> BitList;
template <class GatePtrT>
auto collectTbits(const GatePtrT& gate) -> BitList;
auto collectTbits(const Circuit& circuit) -> BitList;
auto isMctCircuit(const Circuit& circuit) -> bool;
auto isEsopCircuit(const Circuit& circuit) -> bool;
auto getMctCost(const Gate& gate) -> unsigned long long;
template <class GatePtrT>
auto getMctCost(const GatePtrT& gate) -> unsigned long long;
auto calcMctCircuitCost(const Circuit& circuit) -> unsigned long long;
auto sortGatesByCbits(Circuit& circuit) -> void;
auto sortGatesByTbits(Circuit& circuit) -> void;
auto sortGates(Circuit& circuit) -> void;
auto decompIntoSingleTargetCircuits(const Circuit& circuit)
  -> std::unordered_map<Tbit, Circuit>;
}

#include "oracle/oracle_impl.hpp"
