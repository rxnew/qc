/**
 * @file z.hpp
 * @brief header of Z class
 */

#pragma once

#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class ZKernel : public UnitKernel {
 public:
  static constexpr util::string::String const TYPE_NAME = "Z";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "z"
  };

  template <class... Args>
  ZKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> util::string::String const& final;
};

using Z = Unit<ZKernel>;
}

#include "z/z_impl.hpp"
