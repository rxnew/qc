/**
 * @file x.hpp
 * @brief header of X class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class XKernel : public GateKernel {
 public:
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
  virtual auto get_type_name() const -> char const* const& final;
};

template <class... Args>
XKernel::XKernel(Args&&... args) : GateKernel(std::forward<Args>(args)...) {}

inline auto XKernel::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
