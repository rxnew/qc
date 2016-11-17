/**
 * @file library.hpp
 * @brief header about library gates
 */

#pragma once

//#include "library/u.hpp"
//#include "library/i.hpp"
#include "library/x.hpp"
//#include "library/z.hpp"
//#include "library/v.hpp"
//#include "library/s.hpp"
//#include "library/t.hpp"
//#include "library/hadamard.hpp"
//#include "library/swap.hpp"
#include "library/module.hpp"

namespace qc {
template <class... Args>
auto make_gate(std::string const& type_name, Args&&... args) -> Gate;
constexpr auto decode_alias(char const* const alias) -> char const* const;
}

#include "library/library_impl.hpp"
