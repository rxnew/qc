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

inline namespace library {
using S = Unit<SKernel>;
}
}

#include "s/s_impl.hpp"
