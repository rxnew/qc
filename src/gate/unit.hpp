#pragma once

#include "../gate.hpp"

namespace qc {
template <class GateKernelT>
class Unit : public Gate {
 public:
  static constexpr auto const& TYPE = GateKernelT::TYPE;
  static constexpr auto const& TYPE_NAME = GateKernelT::TYPE_NAME;
  static constexpr auto const& ALIASES = GateKernelT::ALIASES;

  template <class... Args>
  explicit Unit(Args&&... args);
  Unit(Unit const& other);
  Unit(Unit&&) noexcept = default;

  ~Unit() noexcept = default;

  auto operator=(Unit const& gate) -> Unit&;
  auto operator=(Unit&& gate) noexcept -> Unit& = default;
};
}

#include "unit/unit_impl.hpp"
