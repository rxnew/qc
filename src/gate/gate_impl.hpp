/**
 * @file gate_impl.hpp
 * @brief implementation header of quantum gate classes
 */

#pragma once

#include <cassert>

#include "gate_core.hpp"
#include "../util/tmpl.hpp"

namespace qc {
inline Gate::Gate(Gate const& other) : core_(other.core_->clone()) {}

template <class Type, class... Args>
inline auto Gate::make(Args&&... args) -> Gate {
  using GateCoreT = util::tmpl::template_parameter_t<Type>;
  return Gate(new GateCoreT(std::forward<Args>(args)...));
}

inline auto Gate::make_dummy(bool assert_flag) -> Gate {
  assert(!assert_flag);
  return Gate(nullptr);
}

inline auto Gate::operator=(Gate const& other) -> Gate& {
  core_ = other.core_->clone();
  return *this;
}

inline auto Gate::operator==(const Gate& other) const -> bool {
  return *core_ == *other.core_;
}

inline auto Gate::operator!=(const Gate& other) const -> bool {
  return !(*this == other);
}

inline auto Gate::get_type_name() const -> char const* const& {
  return core_->get_type_name();
}

inline auto Gate::get_cbits() const -> CBits const& {
  return core_->get_cbits();
}

inline auto Gate::get_tbits() const -> TBits const& {
  return core_->get_tbits();
}

inline auto Gate::set_cbits(CBits const& cbits) -> void {
  core_->cbits_ = cbits;
}

inline auto Gate::set_cbits(CBits&& cbits) -> void {
  core_->cbits_ = std::move(cbits);
}

inline auto Gate::set_tbits(TBits const& tbits) -> void {
  core_->tbits_ = tbits;
}

inline auto Gate::set_tbits(TBits&& tbits) -> void {
  core_->tbits_ = std::move(tbits);
}

inline auto Gate::add_cbit(CBit const& cbit) -> void {
  core_->cbits_.insert(cbit);
}

inline auto Gate::add_cbit(BitNo bit_no, bool polarity) -> void {
  core_->cbits_.emplace(bit_no, polarity);
}

inline auto Gate::add_tbit(TBit const& tbit) -> void {
  core_->tbits_.insert(tbit);
}

inline auto Gate::add_tbit(BitNo bit_no) -> void {
  core_->tbits_.emplace(bit_no);
}

inline auto Gate::has_bit(BitNo bit_no) const -> bool {
  return has_tbit(bit_no) || has_cbit(bit_no);
}

inline auto Gate::has_cbit(CBit const& cbit) const -> bool {
  return core_->cbits_.count(cbit);
}

inline auto Gate::has_cbit(BitNo bit_no) const -> bool {
  return
    has_cbit(CBit(bit_no, true)) ||
    has_cbit(CBit(bit_no, false));
}

inline auto Gate::has_tbit(TBit const& tbit) const -> bool {
  return core_->tbits_.count(tbit);
}

inline auto Gate::has_tbit(BitNo bit_no) const -> bool {
  return has_tbit(TBit(bit_no));
}

inline auto Gate::erase_bit(BitNo bit_no) -> size_t {
  return
    core_->cbits_.erase(get_cbit(bit_no)) ||
    core_->tbits_.erase(TBit(bit_no));
}

inline auto Gate::get_cbit_polarity(BitNo bit_no) const -> bool {
  assert(has_cbit(bit_no));
  return core_->cbits_.count(CBit(bit_no, true));
}

inline auto Gate::is_controlled() const -> bool {
  return !core_->cbits_.empty();
}

inline auto Gate::is_single_controlled() const -> bool {
  return core_->cbits_.size() == 1u;
}

inline auto Gate::is_multi_controlled() const -> bool {
  return core_->cbits_.size() > 1u;
}

inline auto Gate::is_single_target() const -> bool {
  return core_->tbits_.size() == 1u;
}

inline auto Gate::is_multi_target() const -> bool {
  return core_->tbits_.size() > 1u;
}

inline auto Gate::is_single_qubit_rotation() const -> bool {
  return !is_controlled() && is_single_target();
}

inline auto Gate::print(std::ostream& os) const -> void {
  core_->print(os);
}

inline Gate::Gate(std::unique_ptr<GateCore>&& core) : core_(std::move(core)) {}

inline Gate::Gate(GateCore*&& core) : core_(std::move(core)) {}
}
