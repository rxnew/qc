#pragma once

namespace qc {
class X::Impl : public GateImpl {
 public:
  static constexpr char const* const TYPE_NAME = "X";

  template <class... Args>
  Impl(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateImpl> final;
  virtual auto get_type_name() const -> char const* const& final;
};
}

#include "impl/impl_impl.hpp"
