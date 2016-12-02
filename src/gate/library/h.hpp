/**
 * @file h.hpp
 * @brief header of H class
 */

#pragma once

#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class HKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "H";
  static constexpr util::string::Aliases<2> const ALIASES = {
    "h",
    "hadamard"
  };

  template <class... Args>
  HKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

using H = Unit<HKernel>;
}

#include "h/h_impl.hpp"
