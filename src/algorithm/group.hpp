/**
 * @file group.hpp
 * @brief header of group algorithm
 */

#pragma once

#include "../forward_declarations.hpp"

namespace qc {
class GatesWrapperShell;

auto has_group(GatesWrapperShell const& target) -> bool;
auto remove_empty_groups(GatesWrapperShell& target) -> void;
auto expand_groups(GatesWrapperShell& target) -> void;
}
