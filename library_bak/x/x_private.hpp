#pragma once

#include "../x.hpp"

namespace qc {
class X::Impl : public GateImpl {
 public:
  template <class... Args>
  Impl(Args&&... args);

  virtual auto print() -> void final;
};
}

#include "x_impl_private.hpp"
