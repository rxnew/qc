/**
 * @file group.hpp
 * @brief header of Group class
 */

#pragma once

#include "gate_core.hpp"
#include "gate_type.hpp"
#include "gates_wrapper/gates_wrapper_core.hpp"
#include "../gate.hpp"
#include "../util/string/aliases.hpp"

namespace qc {
class GroupCore : public GateCore, public GatesWrapperCore {
 public:
  ~GroupCore() noexcept = default;

 private:
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
  GroupCore(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateCore> final;
  virtual auto get_type_name() const -> char const* const& final;
  virtual auto get_cbits() -> CBits& final;
  virtual auto get_cbits() const -> CBits const& final;
  virtual auto get_tbits() -> TBits& final;
  virtual auto get_tbits() const -> TBits const& final;
  virtual auto print(std::ostream& os = std::cout) const -> void final;
  virtual auto get_gates() -> Gates& final;
  virtual auto get_gates() const -> Gates const& final;

  virtual auto _get_cbits() const -> CBits& final;
  virtual auto _get_tbits() const -> TBits& final;

  mutable CBits m_cbits_;
  mutable TBits m_tbits_;

  friend class Gate;
  friend class GateType<GroupCore>;
};

template <>
class GateType<GroupCore> : public Gate {
 public:
  static constexpr auto const& TYPE_NAME = GroupCore::TYPE_NAME;
  static constexpr auto const& ALIASES = GroupCore::ALIASES;
  static constexpr char const* const BEGIN_TAG = "Group >>";
  static constexpr char const* const END_TAG = "<<";

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
  static auto is_group(Gate const& target) -> bool;

  template <class GateT>
  auto operator=(GateType<GateT> const& gate) -> GateType&;
  template <class GateT>
  auto operator=(GateType<GateT>&& gate) -> GateType&;
};

using Group = GateType<GroupCore>;
}

#include "group/group_impl.hpp"
