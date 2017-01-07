/**
 * @file h.hpp
 * @brief header of H class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class HKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::H;
  static constexpr char const* const TYPE_NAME = "H";
  static constexpr util::string::Aliases<3> const ALIASES = {
    "h",
    "hadamard",
    "snot"
  };

  template <class... Args>
  HKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto bedaggered() const -> bool final;
  virtual auto invert() -> void final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library_gates {
using H = Unit<HKernel>;
}
}

#include "h/h_impl.hpp"
