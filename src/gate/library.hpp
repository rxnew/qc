/**
 * @file library.hpp
 * @brief header about library gates
 */

#pragma once

//#include "library/u.hpp"
#include "library/i.hpp"
#include "library/h.hpp"
#include "library/x.hpp"
#include "library/y.hpp"
#include "library/z.hpp"
#include "library/v.hpp"
#include "library/w.hpp"
#include "library/s.hpp"
#include "library/t.hpp"
#include "library/swap.hpp"

namespace qc {
template <class... Args>
auto make_gate(GateType type, Args&&... args) -> Gate;
template <class... Args>
auto make_gate(std::string const& type_name, Args&&... args) -> Gate;
auto decode_alias(std::string const& alias) -> std::string;
}

#include "library/library_impl.hpp"
