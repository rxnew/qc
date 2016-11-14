/**
 * @file gate_impl.hpp
 * @brief implementation header of quantum gate classes
 */

#pragma once

#include <cassert>

#include "impl.hpp"

namespace qc {
Gate::Gate(Gate const& other) : impl_(other.impl_->clone()) {}

template <class Type, class... Args>
inline auto Gate::make(Args&&... args) -> Gate {
  return Gate(new typename Type::Impl(std::forward<Args>(args)...));
}

inline auto Gate::operator=(Gate const& other) -> Gate& {
  impl_ = other.impl_->clone();
  return *this;
}

inline auto Gate::operator==(const Gate& other) const -> bool {
  return *impl_ == *other.impl_;
}

inline auto Gate::operator!=(const Gate& other) const -> bool {
  return !(*this == other);
}

inline auto Gate::get_type_name() const -> const std::string& {
  return impl_->get_type_name();
}

inline auto Gate::get_cbits() const -> const CBits& {
  return impl_->get_cbits();
}

inline auto Gate::get_tbits() const -> const TBits& {
  return impl_->get_tbits();
}

inline auto Gate::set_cbits(CBits const& cbits) -> void {
  impl_->cbits_ = cbits;
}

inline auto Gate::set_cbits(CBits&& cbits) -> void {
  impl_->cbits_ = std::move(cbits);
}

inline auto Gate::set_tbits(TBits const& tbits) -> void {
  impl_->tbits_ = tbits;
}

inline auto Gate::set_tbits(TBits&& tbits) -> void {
  impl_->tbits_ = std::move(tbits);
}

inline auto Gate::add_cbit(CBit const& cbit) -> void {
  impl_->_add_bit(cbit);
}

inline auto Gate::add_cbit(BitNo bit_no, bool polarity) -> void {
  impl_->cbits_.emplace(bit_no, polarity);
}

inline auto Gate::add_tbit(TBit const& tbit) -> void {
  impl_->_add_bit(tbit);
}

inline auto Gate::add_tbit(BitNo bit_no) -> void {
  impl_->tbits_.emplace(bit_no);
}

inline auto Gate::has_bit(BitNo bit_no) const -> bool {
  return has_tbit(bit_no) || has_cbit(bit_no);
}

inline auto Gate::has_cbit(CBit const& cbit) const -> bool {
  return impl_->cbits_.count(cbit);
}

inline auto Gate::has_cbit(BitNo bit_no) const -> bool {
  return
    has_cbit(CBit(bit_no, true)) ||
    has_cbit(CBit(bit_no, false));
}

inline auto Gate::has_tbit(TBit const& tbit) const -> bool {
  return impl_->tbits_.count(tbit);
}

inline auto Gate::has_tbit(BitNo bit_no) const -> bool {
  return has_tbit(TBit(bit_no));
}

inline auto Gate::erase_bit(BitNo bit_no) -> size_t {
  return
    impl_->cbits_.erase(get_cbit(bit_no)) ||
    impl_->tbits_.erase(TBit(bit_no));
}

inline auto Gate::get_cbit_polarity(BitNo bit_no) const -> bool {
  assert(has_cbit(bit_no));
  return impl_->cbits_.count(CBit(bit_no, true));
}

inline auto Gate::is_controlled() const -> bool {
  return !impl_->cbits_.empty();
}

inline auto Gate::is_single_controlled() const -> bool {
  return impl_->cbits_.size() == 1u;
}

inline auto Gate::is_multi_controlled() const -> bool {
  return impl_->cbits_.size() > 1u;
}

inline auto Gate::is_single_target() const -> bool {
  return impl_->tbits_.size() == 1u;
}

inline auto Gate::is_multi_target() const -> bool {
  return impl_->tbits_.size() > 1u;
}

inline auto Gate::is_single_qubit_rotation() const -> bool {
  return !is_controlled() && is_single_target();
}

inline auto Gate::print(std::ostream& os) const -> void {
  impl_->print(os);
}

inline Gate::Gate(std::unique_ptr<Impl>&& impl) : impl_(std::move(impl)) {}

inline Gate::Gate(Impl*&& impl) : impl_(std::move(impl_)) {}
}
