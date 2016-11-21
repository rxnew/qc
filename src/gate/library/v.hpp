/**
 * @file v.hpp
 * @brief header of V class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class VKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "V";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "v"
  };

  template <class... Args>
  VKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class VDaggerKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "V*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "v*",
    "v+",
    "vdagger",
    "vplus"
  };

  template <class... Args>
  VDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using V = GateType<VKernel>;
using VDagger = GateType<VDaggerKernel>;
}

#include "v/v_impl.hpp"
