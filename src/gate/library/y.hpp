/**
 * @file y.hpp
 * @brief header of Y class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class YKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::Y;
  static constexpr char const* const TYPE_NAME = "Y";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "y"
  };

  template <class... Args>
  YKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto be_daggered() const -> bool final;
  virtual auto invert() -> void final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library {
using Y = Unit<YKernel>;
}
}

#include "y/y_impl.hpp"
