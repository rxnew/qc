/**
 * @file w.hpp
 * @brief header of W class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class WCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "W";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "w"
  };

  template <class... Args>
  WCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class WDaggerCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "W*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "w*",
    "w+",
    "wdagger",
    "wplus"
  };

  template <class... Args>
  WDaggerCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using W = GateType<WCore>;
using WDagger = GateType<WDaggerCore>;
}

#include "w/w_impl.hpp"
