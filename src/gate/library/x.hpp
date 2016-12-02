/**
 * @file x.hpp
 * @brief header of X class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class XKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::X;
  static constexpr char const* const TYPE_NAME = "X";
  static constexpr util::string::Aliases<5> const ALIASES = {
    "x",
    "not",
    "toffoli",
    "mct",
    "mpmct"
  };

  template <class... Args>
  XKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto is_dagger() const -> bool final;
  virtual auto get_type() const -> GateType final;
  virtual auto get_type_name() const -> std::string final;
};

inline namespace library {
using X = Unit<XKernel>;
}
}

#include "x/x_impl.hpp"
