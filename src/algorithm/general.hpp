/**
 * @file general.hpp
 * @brief header of general algorithm
 */

#pragma once

#include "../forward_declarations.hpp"

namespace qc {
auto get_cbit(Gate const& gate) -> CBit const&;
auto get_tbit(Gate const& gate) -> TBit const&;
auto decomp_to_single_target_gates(Gate const& gate) -> Gates;
auto decomp_to_single_target_gates(Circuit& circuit) -> void;
}

#include "general/general_impl.hpp"
