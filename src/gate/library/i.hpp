/**
 * @file i.hpp
 * @brief header of I class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class IKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "I";
  static constexpr util::string::Aliases<2> const ALIASES = {
    "i",
    "identity"
  };

  template <class... Args>
  IKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using I = GateType<IKernel>;
}

#include "i/i_impl.hpp"
