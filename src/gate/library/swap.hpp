/**
 * @file swap.hpp
 * @brief header of Swap class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class SwapKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::Swap;
  static constexpr char const* const TYPE_NAME = "Swap";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "swap"
  };

  template <class... Args>
  SwapKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

using Swap = Unit<SwapKernel>;
}

#include "swap/swap_impl.hpp"
