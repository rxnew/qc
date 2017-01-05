/**
 * @file z.hpp
 * @brief header of Z class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class ZKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::Z;
  static constexpr char const* const TYPE_NAME = "Z";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "z"
  };

  template <class... Args>
  ZKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto bedaggered() const -> bool final;
  virtual auto invert() -> void final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library_gates {
using Z = Unit<ZKernel>;
}
}

#include "z/z_impl.hpp"
