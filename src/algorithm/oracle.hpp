/**
 * @file oracle.hpp
 * @brief header of algorithm for quantum oracle
 */

#pragma once

#include "../forward_declarations.hpp"

namespace qc {
auto collect_cbits(Gate const& gate) -> BitNos;
auto collect_cbits(Circuit const& circuit) -> BitNos;
auto collect_tbits(Gate const& gate) -> BitNos;
auto collect_tbits(Circuit const& circuit) -> BitNos;
auto is_mct_circuit(Circuit const& circuit) -> bool;
auto is_esop_circuit(Circuit const& circuit) -> bool;
auto get_mct_cost(Gate const& gate, bool decomp_flag = false)
  -> unsigned long long;
auto calculate_mct_circuit_cost(Circuit const& circuit,
                                bool decomp_flag = false) -> unsigned long long;
auto sort_gates_by_cbits(Circuit& circuit) -> void;
auto sort_gates_by_tbits(Circuit& circuit) -> void;
auto sort_gates(Circuit& circuit) -> void;
auto decomp_to_single_target_circuits(Circuit const& circuit)
  -> std::unordered_map<TBit, Circuit>;
}

#include "oracle/oracle_impl.hpp"
