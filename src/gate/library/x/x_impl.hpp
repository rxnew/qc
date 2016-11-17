#pragma once

namespace qc {
class X::Impl : public GateImpl {
 public:
  template <class... Args>
  Impl(Args&&... args);

  virtual auto clone() const -> std::unique_ptr<GateImpl> final;
  virtual auto get_type_name() const -> char const* const& final;
};

template <class... Args>
X::Impl::Impl(Args&&... args) : GateImpl(std::forward<Args>(args)...) {}

inline auto X::Impl::clone() const -> std::unique_ptr<GateImpl> {
  return std::make_unique<Impl>(*this);
}

inline auto X::Impl::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
