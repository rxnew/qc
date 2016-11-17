/**
 * @file module.hpp
 * @brief header of Module class
 */

#pragma once

#include "../../gate.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class Module : private GateType {
 public:
  static char const* const TYPE_NAME;
  static util::string::Aliases<5> const ALIASES;

  static auto is_module(Gate const& target) -> bool;
  static auto get(Gate const& target) -> Gates const&;
  template <class GatesT>
  static auto set(Gate& target, GatesT&& gates) -> void;
  static auto add(Gate& target, Gate const& gate) -> void;
  static auto add(Gate& target, Gate&& gate) -> void;

 private:
  class Impl;

  friend class Gate;
};
}

#include "module/module_impl.hpp"
