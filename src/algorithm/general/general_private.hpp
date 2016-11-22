/**
 * @file general_private.hpp
 * @brief private header of general algorithm
 */

#pragma once

#include "../../forward_declarations.hpp"

namespace qc {
class GatesWrapperShell;

auto _decomp_to_single_target_gates(GatesWrapperShell const& target) -> Gates;
}
