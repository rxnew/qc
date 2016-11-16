/**
 * @file x.hpp
 * @brief header of X class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
class X : private GateType {
 public:
  static char const constexpr* const TYPE_NAME = "X";

 private:
  class Impl;

  friend class Gate;
};
}

#include "x/x_impl.hpp"
