/**
 * @file x.hpp
 * @brief header of X class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class XCore : public GateCore {
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
  XCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using X = GateType<XCore>;
}

#include "x/x_impl.hpp"
