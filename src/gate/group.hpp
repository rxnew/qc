/**
 * @file group.hpp
 * @brief header of Group class
 */

#pragma once

#include "gate_kernel.hpp"
#include "gate_type.hpp"
#include "gates_wrapper/gates_wrapper_kernel.hpp"
#include "../gate.hpp"
#include "../util/string/aliases.hpp"

namespace qc {
class GroupKernel : public GateKernel, public GatesWrapperKernel {
 public:
  static constexpr char const* const TYPE_NAME = "Group";
  static constexpr util::string::Aliases<6> const ALIASES = {
    "group",
    "module",
    "macrogate",
    "gatearray",
    "step",
    "pqgate"
  };

  template <class... Args>
  GroupKernel(Args&&... args);

  ~GroupKernel() noexcept = default;

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> char const* const& final;
  virtual auto get_cbits() -> CBits& final;
  virtual auto get_cbits() const -> CBits const& final;
  virtual auto get_tbits() -> TBits& final;
  virtual auto get_tbits() const -> TBits const& final;
  virtual auto print(std::ostream& os = std::cout) const -> void final;
  virtual auto get_gates() -> Gates& final;
  virtual auto get_gates() const -> Gates const& final;

 private:
  virtual auto _get_cbits() const -> CBits& final;
  virtual auto _get_tbits() const -> TBits& final;

  mutable CBits m_cbits_;
  mutable TBits m_tbits_;
};

template <>
class GateType<GroupKernel> : public Gate {
 public:
  static constexpr auto const& TYPE_NAME = GroupKernel::TYPE_NAME;
  static constexpr auto const& ALIASES = GroupKernel::ALIASES;
  static constexpr char const* const BEGIN_TAG = R"(Group \)";
  static constexpr char const* const END_TAG = R"(\)";

  template <class... Args>
  GateType(Args&&... args);
  GateType(GateType const& other);
  GateType(GateType&&) noexcept = default;
  template <class GateT>
  GateType(GateType<GateT> const& gate);
  template <class GateT>
  GateType(GateType<GateT>&& gate);

  ~GateType() noexcept = default;

  template <class... Args>
  static auto make(Args&&... args) -> Gate;

  template <class GateT>
  auto operator=(GateType<GateT> const& gate) -> GateType&;
  template <class GateT>
  auto operator=(GateType<GateT>&& gate) -> GateType&;
};

using Group = GateType<GroupKernel>;
}

#include "group/group_impl.hpp"
