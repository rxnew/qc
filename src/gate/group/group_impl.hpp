#pragma once

namespace qc {
class Group::Impl : public GateImpl {
 public:
  Impl() = default;
  Impl(Gate const& gate);
  Impl(Gate&& gate);
  Impl(Gates const& gates);
  Impl(Gates&& gates);
  Impl(std::initializer_list<Gate> list);
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
  virtual auto _get_gates() -> Gates& final;
  virtual auto _get_gates() const -> Gates const& final;

  Gates gates_;

  mutable CBits m_cbits_;
  mutable TBits m_tbits_;
};

template <class... Args>
auto Group::make(Args&&... args) -> Gate {
  auto gate = Gate::make_dummy(false);
  GateType::_get_impl(gate)
    = std::make_unique<Impl>(std::forward<Args>(args)...);
  return gate;
}

inline auto Group::is_group(Gate const& target) -> bool {
  return ALIASES == target.get_type_name();
}

inline auto Group::get_gates(Gate const& target) -> Gates const& {
  assert(is_group(target));
  return GateType::_get_impl(target)->_get_gates();
}

template <class GatesT>
inline auto Group::set_gates(Gate& target, GatesT&& gates) -> void {
  assert(is_group(target));
  GateType::_get_impl(target)->_get_gates() = std::forward<GatesT>(gates);
}

inline auto Group::add_gate(Gate& target, Gate const& gate) -> void {
  assert(is_group(target));
  GateType::_get_impl(target)->_get_gates().push_back(gate);
}

inline auto Group::add_gate(Gate& target, Gate&& gate) -> void {
  assert(is_group(target));
  GateType::_get_impl(target)->_get_gates().push_back(std::move(gate));
}

inline Group::Impl::Impl(Gate const& gate) : gates_{gate} {}

inline Group::Impl::Impl(Gate&& gate) : gates_{std::move(gate)} {}

inline Group::Impl::Impl(Gates const& gates) : gates_(gates) {}

inline Group::Impl::Impl(Gates&& gates) : gates_(std::move(gates)) {}

inline Group::Impl::Impl(std::initializer_list<Gate> list) : gates_(list) {}

inline Group::Impl::Impl(Impl const& other) : gates_(other.gates_) {}

inline Group::Impl::Impl(Impl&& other) : gates_(std::move(other.gates_)) {}

inline auto Group::Impl::clone() const -> std::unique_ptr<GateImpl> {
  return std::make_unique<Impl>(*this);
}

inline auto Group::Impl::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}

inline auto Group::Impl::get_cbits() -> CBits& {
  return _get_cbits();
}

inline auto Group::Impl::get_cbits() const -> const CBits& {
  return _get_cbits();
}

inline auto Group::Impl::get_tbits() -> TBits& {
  return _get_tbits();
}

inline auto Group::Impl::get_tbits() const -> const TBits& {
  return _get_tbits();
}

inline auto Group::Impl::_get_gates() -> Gates& {
  return gates_;
}

inline auto Group::Impl::_get_gates() const -> Gates const& {
  return gates_;
}
}
