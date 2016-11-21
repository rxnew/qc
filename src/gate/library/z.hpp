/**
 * @file z.hpp
 * @brief header of Z class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class ZCore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "Z";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "z"
  };

  template <class... Args>
  ZCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using Z = GateType<ZCore>;
}

#include "z/z_impl.hpp"
