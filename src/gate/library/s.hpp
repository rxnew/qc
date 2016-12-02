/**
 * @file s.hpp
 * @brief header of S class
 */

#pragma once

#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class SKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "S";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "s"
  };

  template <class... Args>
  SKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

class SDaggerKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "S*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "s*",
    "s+",
    "sdagger",
    "splus"
  };

  template <class... Args>
  SDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

using S = Unit<SKernel>;
using SDagger = Unit<SDaggerKernel>;
}

#include "s/s_impl.hpp"
