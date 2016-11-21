/**
 * @file v.hpp
 * @brief header of V class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class VCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "V";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "v"
  };

  template <class... Args>
  VCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class VDaggerCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "V*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "v*",
    "v+",
    "vdagger",
    "vplus"
  };

  template <class... Args>
  VDaggerCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using V = GateType<VCore>;
using VDagger = GateType<VDaggerCore>;
}

#include "v/v_impl.hpp"
