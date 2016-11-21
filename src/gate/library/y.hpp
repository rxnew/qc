/**
 * @file y.hpp
 * @brief header of Y class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class YCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "Y";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "y"
  };

  template <class... Args>
  YCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using Y = GateType<YCore>;
}

#include "y/y_impl.hpp"
