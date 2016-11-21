/**
 * @file y.hpp
 * @brief header of Y class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class YKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "Y";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "y"
  };

  template <class... Args>
  YKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using Y = GateType<YKernel>;
}

#include "y/y_impl.hpp"
