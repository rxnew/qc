/**
 * @file w.hpp
 * @brief header of W class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class WKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "W";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "w"
  };

  template <class... Args>
  WKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class WDaggerKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "W*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "w*",
    "w+",
    "wdagger",
    "wplus"
  };

  template <class... Args>
  WDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using W = GateType<WKernel>;
using WDagger = GateType<WDaggerKernel>;
}

#include "w/w_impl.hpp"
