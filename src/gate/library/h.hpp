/**
 * @file h.hpp
 * @brief header of H class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class HCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "H";
  static constexpr util::string::Aliases<2> const ALIASES = {
    "h",
    "hadamard"
  };

  template <class... Args>
  HCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using H = GateType<HCore>;
}

#include "h/h_impl.hpp"
