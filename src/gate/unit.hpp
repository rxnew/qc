#pragma once

#include "../gate.hpp"
#include "../util/tmpl.hpp"

namespace qc {
template <class GateKernelT>
class Unit : public Gate {
 public:
  static constexpr auto const& TYPE = GateKernelT::TYPE;
  static constexpr auto const& TYPE_NAME = GateKernelT::TYPE_NAME;
  static constexpr auto const& ALIASES = GateKernelT::ALIASES;

  Unit();
  template <class... Args,
            class = util::tmpl::disable_if_t<
              util::tmpl::is_same_plain_variadic_v<Unit, Args...>>>
  explicit Unit(Args&&... args);
  Unit(Unit const& other);
  Unit(Unit&&) noexcept = default;

  ~Unit() noexcept = default;

  auto operator=(Unit const& gate) -> Unit&;
  auto operator=(Unit&& gate) noexcept -> Unit& = default;
};
}

#include "unit/unit_impl.hpp"
