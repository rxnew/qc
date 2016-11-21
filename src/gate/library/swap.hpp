/**
 * @file swap.hpp
 * @brief header of Swap class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class SwapCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "Swap";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "swap"
  };

  template <class... Args>
  SwapCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using Swap = GateType<SwapCore>;
}

#include "swap/swap_impl.hpp"
