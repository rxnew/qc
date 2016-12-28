/**
 * @file v.hpp
 * @brief header of V class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class VKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::V;
  static constexpr char const* const TYPE_NAME = "V";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "v"
  };

  template <class... Args>
  VKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library_gates {
using V = Unit<VKernel>;
}
}

#include "v/v_impl.hpp"
