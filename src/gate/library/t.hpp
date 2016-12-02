/**
 * @file t.hpp
 * @brief header of T class
 */

#pragma once

#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class TKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "T";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "t"
  };

  template <class... Args>
  TKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

class TDaggerKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "T*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "t*",
    "t+",
    "tdagger",
    "tplus"
  };

  template <class... Args>
  TDaggerKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

using T = Unit<TKernel>;
using TDagger = Unit<TDaggerKernel>;
}

#include "t/t_impl.hpp"
