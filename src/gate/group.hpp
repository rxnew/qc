/**
 * @file group.hpp
 * @brief header of Group class
 */

#pragma once

#include "../gate.hpp"
#include "../util/string/aliases.hpp"

namespace qc {
class Group : private GateType {
 public:
  static char const* const TYPE_NAME;
  static util::string::Aliases<6> const ALIASES;
  static char const* const BEGIN_TAG;
  static char const* const END_TAG;

  template <class... Args>
  static auto make(Args&&... args) -> Gate;
  static auto make(std::initializer_list<Gate> list) -> Gate;
  static auto is_group(Gate const& target) -> bool;
  static auto get_gates(Gate const& target) -> Gates const&;
  template <class GatesT>
  static auto set_gates(Gate& target, GatesT&& gates) -> void;
  static auto add_gate(Gate& target, Gate const& gate) -> void;
  static auto add_gate(Gate& target, Gate&& gate) -> void;

 private:
  class Impl;

  friend class Gate;
};
}

#include "group/group_impl.hpp"
