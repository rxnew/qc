/**
 * @file t.hpp
 * @brief header of T class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class TKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "T";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "t"
  };

  template <class... Args>
  TKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class TDaggerKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "T*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "t*",
    "t+",
    "tdagger",
    "tplus"
  };

  template <class... Args>
  TDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using T = GateType<TKernel>;
using TDagger = GateType<TDaggerKernel>;
}

#include "t/t_impl.hpp"
