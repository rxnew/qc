/**
 * @file t.hpp
 * @brief header of T class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class TKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::T;
  static constexpr char const* const TYPE_NAME = "T";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "t"
  };

  template <class... Args>
  TKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

class TDaggerKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::TDagger;
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
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library {
using T = Unit<TKernel>;
using TDagger = Unit<TDaggerKernel>;
}
}

#include "t/t_impl.hpp"
