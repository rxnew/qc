/**
 * @file s.hpp
 * @brief header of S class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class SKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "S";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "s"
  };

  template <class... Args>
  SKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class SDaggerKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "S*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "s*",
    "s+",
    "sdagger",
    "splus"
  };

  template <class... Args>
  SDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using S = GateType<SKernel>;
using SDagger = GateType<SDaggerKernel>;
}

#include "s/s_impl.hpp"
