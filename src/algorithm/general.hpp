/**
 * @file general.hpp
 * @brief header of general algorithm
 */

#pragma once

#include "../gate/library.hpp"
#include "../circuit.hpp"

namespace qc {
auto getGateTypeName(const std::string& str) -> const std::string&;
template <class GatePtrT = GatePtr, class... Args>
static auto createGate(const std::string& str, Args&&... args) -> GatePtrT;
template <class GatePtrT = GatePtr, class... Args>
static auto createGate(const Matrix& target_matrix, Args&&... args) -> GatePtrT;
template <class GatePtrT>
auto getCbit(const GatePtrT& gate) -> const Cbit&;
template <class GatePtrT>
auto getTbit(const GatePtrT& gate) -> const Tbit&;
template <class GatePtrT, class GateListT = std::list<GatePtrT>>
auto decompIntoSingleTargetGates(const GatePtrT& gate) -> GateListT;
auto decompIntoSingleTargetGates(Circuit& circuit) -> void;
}

#include "general/general_impl.hpp"
