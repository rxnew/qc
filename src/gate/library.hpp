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
auto make_gate(GateType type,
               std::initializer_list<CBit> cbits,
               std::initializer_list<TBit> tbits) -> Gate;
auto make_gate(GateType type,
               bool bedaggered,
               std::initializer_list<CBit> cbits,
               std::initializer_list<TBit> tbits) -> Gate;
template <class... Args>
auto make_gate(GateType type, Args&&... args) -> Gate;
auto make_gate(std::string const& type_name,
               std::initializer_list<CBit> cbits,
               std::initializer_list<TBit> tbits) -> Gate;
template <class... Args>
auto make_gate(std::string const& type_name, Args&&... args) -> Gate;
auto decode_alias(std::string const& alias, bool assert_flag = false)
  -> std::string;
}

#include "library/library_impl.hpp"
