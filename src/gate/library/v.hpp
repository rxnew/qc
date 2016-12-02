/**
 * @file v.hpp
 * @brief header of V class
 */

#pragma once

#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class VKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "V";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "v"
  };

  template <class... Args>
  VKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

class VDaggerKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "V*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "v*",
    "v+",
    "vdagger",
    "vplus"
  };

  template <class... Args>
  VDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

using V = Unit<VKernel>;
using VDagger = Unit<VDaggerKernel>;
}

#include "v/v_impl.hpp"
