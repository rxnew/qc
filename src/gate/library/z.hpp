/**
 * @file z.hpp
 * @brief header of Z class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class ZKernel : public GateKernel {
 public:
  static constexpr char const* const TYPE_NAME = "Z";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "z"
  };

  template <class... Args>
  ZKernel(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using Z = GateType<ZKernel>;
}

#include "z/z_impl.hpp"
