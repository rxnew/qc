/**
 * @file t.hpp
 * @brief header of T class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class TCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "T";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "t"
  };

  template <class... Args>
  TCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

class TDaggerCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "T*";
  static constexpr util::string::Aliases<4> const ALIASES = {
    "t*",
    "t+",
    "tdagger",
    "tplus"
  };

  template <class... Args>
  TDaggerCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using T = GateType<TCore>;
using TDagger = GateType<TDaggerCore>;
}

#include "t/t_impl.hpp"
