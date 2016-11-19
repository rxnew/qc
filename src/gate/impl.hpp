#pragma once

namespace qc {
/**
 * @brief quantum gate class
 * @note this class is abstract
 */
class Gate::Impl {
 public:
  Impl() = default;
  explicit Impl(TBit const& tbit);
  Impl(CBit const& cbit, TBit const& tbit);
  Impl(CBit const& cbit, TBits const& tbits);
  Impl(CBit const& cbit, TBits&& tbits);
  Impl(CBits const& cbits, TBit const& tbit);
  Impl(CBits&& cbits, TBit const& tbit);
  Impl(CBits const& cbits, TBits const& tbits);
  Impl(CBits&& cbits, TBits&& tbits);
  //template <class... Args>
  //explict Impl(Args&&... args);
  Impl(Impl const&) = default;
  Impl(Impl&&) noexcept = default;

  virtual ~Impl() noexcept = default;

  auto operator=(Impl const&) -> Impl& = default;
  auto operator=(Impl&&) noexcept -> Impl& = default;
  auto operator==(Impl const& other) const -> bool;
  auto operator!=(Impl const& other) const -> bool;

  virtual auto clone() const -> std::unique_ptr<Impl> = 0;
  virtual auto get_type_name() const -> char const* const& = 0;
  virtual auto get_cbits() -> CBits&;
  virtual auto get_cbits() const -> CBits const&;
  virtual auto get_tbits() -> TBits&;
  virtual auto get_tbits() const -> TBits const&;
  virtual auto print(std::ostream& os = std::cout) const -> void;

  // for GateGroup
  virtual auto _get_gates() -> Gates&;
  virtual auto _get_gates() const -> Gates const&;
  auto _make_gates() const -> Gates&;

  CBits cbits_;
  TBits tbits_;

 private:
  auto _add_bit(CBit const& cbit) -> void;
  auto _add_bit(CBit&& tbit) -> void;
  auto _add_bit(TBit const& cbit) -> void;
  auto _add_bit(TBit&& tbit) -> void;
  template <class BitT, class... Args>
  auto _add_bit(BitT&& bit, Args&&... args) -> void;

  friend class Gate;
};

class GateType {
 protected:
  using GateImpl = Gate::Impl;

  static auto _get_impl(Gate& gate) -> std::unique_ptr<GateImpl>&;
  static auto _get_impl(Gate const& gate) -> std::unique_ptr<GateImpl> const&;
};
}

#include "impl/impl_impl.hpp"
