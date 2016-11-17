#pragma once

namespace qc {
class Module::Impl : public GateImpl {
 public:
  Impl() = default;
  Impl(Gate const& inner);
  Impl(Gate&& inner);
  Impl(Gates const& inners);
  Impl(Gates&& inners);
  template <class... Args>
  Impl(Args&&... args);
  Impl(Impl const& other);
  Impl(Impl&& other);

  ~Impl() = default;

  virtual auto clone() const -> std::unique_ptr<GateImpl> final;
  virtual auto get_type_name() const -> char const* const& final;
  virtual auto get_cbits() -> CBits& final;
  virtual auto get_cbits() const -> CBits const& final;
  virtual auto get_tbits() -> TBits& final;
  virtual auto get_tbits() const -> TBits const& final;
  virtual auto print(std::ostream& os = std::cout) const -> void final;

 private:
  auto _get_cbits() const -> CBits&;
  auto _get_tbits() const -> TBits&;
  virtual auto _get_inners() -> Gates& final;
  virtual auto _get_inners() const -> Gates const& final;

  Gates inners_;

  mutable CBits m_cbits_;
  mutable TBits m_tbits_;
};

inline auto Module::is_module(Gate const& target) -> bool {
  return ALIASES == target.get_type_name();
}

inline auto Module::get(Gate const& target) -> Gates const& {
  assert(is_module(target));
  return GateType::get_impl(target)->_get_inners();
}

template <class GatesT>
inline auto Module::set(Gate& target, GatesT&& gates) -> void {
  assert(is_module(target));
  GateType::get_impl(target)->_get_inners() = std::forward<GatesT>(gates);
}

inline auto Module::add(Gate& target, Gate const& gate) -> void {
  assert(is_module(target));
  GateType::get_impl(target)->_get_inners().push_back(gate);
}

inline auto Module::add(Gate& target, Gate&& gate) -> void {
  assert(is_module(target));
  GateType::get_impl(target)->_get_inners().push_back(std::move(gate));
}

inline Module::Impl::Impl(Gate const& inner) : inners_{inner} {}

inline Module::Impl::Impl(Gate&& inner) : inners_{std::move(inner)} {}

inline Module::Impl::Impl(Gates const& inners) : inners_(inners) {}

inline Module::Impl::Impl(Gates&& inners) : inners_(std::move(inners)) {}

template <class... Args>
inline Module::Impl::Impl(Args&&... args)
  : Gate::Impl(std::forward<Args>(args)...) {}

inline Module::Impl::Impl(Impl const& other) : inners_(other.inners_) {}

inline Module::Impl::Impl(Impl&& other) : inners_(std::move(other.inners_)) {}

inline auto Module::Impl::clone() const -> std::unique_ptr<GateImpl> {
  return std::make_unique<Impl>(*this);
}

inline auto Module::Impl::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

inline auto Module::Impl::get_cbits() -> CBits& {
  return _get_cbits();
}

inline auto Module::Impl::get_cbits() const -> const CBits& {
  return _get_cbits();
}

inline auto Module::Impl::get_tbits() -> TBits& {
  return _get_tbits();
}

inline auto Module::Impl::get_tbits() const -> const TBits& {
  return _get_tbits();
}

inline auto Module::Impl::_get_inners() -> Gates& {
  return inners_;
}

inline auto Module::Impl::_get_inners() const -> Gates const& {
  return inners_;
}
}
