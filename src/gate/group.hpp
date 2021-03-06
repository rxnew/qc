/**
 * @file group.hpp
 * @brief header of Group class
 */

#pragma once

#include "gate_kernel/group_kernel.hpp"
#include "unit.hpp"

namespace qc {
template <>
class Unit<GroupKernel> : public Gate {
 public:
  static constexpr auto const& TYPE = GroupKernel::TYPE;
  static constexpr auto const& TYPE_NAME = GroupKernel::TYPE_NAME;
  static constexpr auto const& ALIASES = GroupKernel::ALIASES;
  static constexpr char const* const BEGIN_TAG = R"(Group \)";
  static constexpr char const* const END_TAG = R"(\)";

  Unit();
  template <class... Args,
            class = util::tmpl::disable_if_t<
              util::tmpl::is_same_plain_variadic_v<Unit, Args...>>>
  explicit Unit(Args&&... args);
  Unit(Unit const& other);
  Unit(Unit&&) noexcept = default;

  ~Unit() noexcept = default;

  template <class... Args>
  static auto make(Args&&... args) -> Gate;

  auto operator=(Unit const& gate) -> Unit&;
  auto operator=(Unit&& gate) noexcept -> Unit& = default;
};

using Group = Unit<GroupKernel>;

template <class... Args>
auto make_group(Args&&... args) -> Gate;
}

#include "group/group_impl.hpp"
