/**
 * @file x.hpp
 * @brief header of X class
 */

#pragma once

#include "../../gate.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class X : private GateType {
 public:
  static char const* const TYPE_NAME;
  static util::string::Aliases<5> const ALIASES;

 private:
  class Impl;

  friend class Gate;
};
}

#include "x/x_impl.hpp"
