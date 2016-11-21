/**
 * @file s.hpp
 * @brief header of S class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class SCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "S";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "s"
  };

  template <class... Args>
  SCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class SDaggerCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "S*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "s*",
    "s+",
    "sdagger",
    "splus"
  };

  template <class... Args>
  SDaggerCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using S = GateType<SCore>;
using SDagger = GateType<SDaggerCore>;
}

#include "s/s_impl.hpp"
