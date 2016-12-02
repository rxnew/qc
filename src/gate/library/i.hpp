/**
 * @file i.hpp
 * @brief header of I class
 */

#pragma once

#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class IKernel : public UnitKernel {
 public:
  static constexpr char const* const TYPE_NAME = "I";
  static constexpr util::string::Aliases<2> const ALIASES = {
    "i",
    "identity"
  };

  template <class... Args>
  IKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> std::string final;
};

using I = Unit<IKernel>;
}

#include "i/i_impl.hpp"
