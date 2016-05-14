/**
 * @file general.hpp
 * @brief header of general algorithm
 */

#pragma once

#include "../gate/library.hpp"
#include "../circuit.hpp"

namespace qc {
auto getGateTypeName(const std::string& str) -> const std::string&;
template <class... Args>
static auto createGate(const std::string& str, Args&&... args) -> GatePtr;
template <class... Args>
static auto createGate(const Matrix& target_matrix, Args&&... args) -> GatePtr;
auto getCbit(const GatePtr& gate) -> const Cbit&;
auto getTbit(const GatePtr& gate) -> const Tbit&;
auto decompIntoSingleTargetGates(const GatePtr& gate) -> GateList;
auto decompIntoSingleTargetGates(Circuit& circuit) -> void;
}

#include "general/general_impl.hpp"
