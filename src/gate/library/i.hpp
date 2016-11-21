/**
 * @file i.hpp
 * @brief header of I class
 */

#pragma once

#include "../gate_type.hpp"
#include "../gate_core.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class ICore : public GateCore {
 public:
  static constexpr char const* const TYPE_NAME = "I";
  static constexpr util::string::Aliases<2> const ALIASES = {
    "i",
    "identity"
  };

  template <class... Args>
  ICore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
};

using I = GateType<ICore>;
}

#include "i/i_impl.hpp"
