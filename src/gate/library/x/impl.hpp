#pragma once

namespace qc {
class X::Impl : public GateImpl {
 public:
  template <class... Args>
  Impl(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateImpl> final;
  virtual auto get_type_name() const -> char const* const& final;
};
}

#include "impl/impl_impl.hpp"
