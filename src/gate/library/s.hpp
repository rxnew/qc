/**
 * @file s.hpp
 * @brief header of S class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class SKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::S;
  static constexpr char const* const TYPE_NAME = "S";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "s"
  };

  template <class... Args>
  SKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

class SDaggerKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::SDagger;
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
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library {
using S = Unit<SKernel>;
using SDagger = Unit<SDaggerKernel>;
}
}

#include "s/s_impl.hpp"
