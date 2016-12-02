/**
 * @file w.hpp
 * @brief header of W class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class WKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::W;
  static constexpr char const* const TYPE_NAME = "W";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "w"
  };

  template <class... Args>
  WKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library {
using W = Unit<WKernel>;
}
}

#include "w/w_impl.hpp"
