/**
 * @file w.hpp
 * @brief header of W class
 */

#pragma once

#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class WKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "W";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "w"
  };

  template <class... Args>
  WKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

class WDaggerKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "W*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "w*",
    "w+",
    "wdagger",
    "wplus"
  };

  template <class... Args>
  WDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

using W = Unit<WKernel>;
using WDagger = Unit<WDaggerKernel>;
}

#include "w/w_impl.hpp"
