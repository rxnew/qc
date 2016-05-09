/**
 * @file library.hpp
 * @brief header about library gates
 */

#pragma once

#include "library/u.hpp"
#include "library/i.hpp"
#include "library/x.hpp"
#include "library/z.hpp"
#include "library/v.hpp"
#include "library/s.hpp"
#include "library/t.hpp"
#include "library/hadamard.hpp"
#include "library/swap.hpp"

namespace qc {
template <class... Args>
static auto createGate(const std::string& str, Args&&... args) -> GatePtr;
template <class... Args>
static auto createGate(const Matrix& target_matrix, Args&&... args) -> GatePtr;
}

#include "library/library_impl.hpp"
