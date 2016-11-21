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
  core_->get_cbits() = cbits;
}

inline auto Gate::set_cbits(CBits&& cbits) -> void {
  core_->get_cbits() = std::move(cbits);
}

inline auto Gate::set_tbits(TBits const& tbits) -> void {
  core_->get_tbits() = tbits;
}

inline auto Gate::set_tbits(TBits&& tbits) -> void {
  core_->get_tbits() = std::move(tbits);
}

inline auto Gate::add_cbit(CBit const& cbit) -> void {
  core_->get_cbits().insert(cbit);
}

inline auto Gate::add_cbit(BitNo bit_no, bool polarity) -> void {
  core_->get_cbits().emplace(bit_no, polarity);
}

inline auto Gate::add_tbit(TBit const& tbit) -> void {
  core_->get_tbits().insert(tbit);
}

inline auto Gate::add_tbit(BitNo bit_no) -> void {
  core_->get_tbits().emplace(bit_no);
}

inline auto Gate::has_bit(BitNo bit_no) const -> bool {
  return has_tbit(bit_no) || has_cbit(bit_no);
}

inline auto Gate::has_cbit(CBit const& cbit) const -> bool {
  return core_->get_cbits().count(cbit);
}

inline auto Gate::has_cbit(BitNo bit_no) const -> bool {
  return
    has_cbit(CBit(bit_no, true)) ||
    has_cbit(CBit(bit_no, false));
}

inline auto Gate::has_tbit(TBit const& tbit) const -> bool {
  return core_->get_tbits().count(tbit);
}

inline auto Gate::has_tbit(BitNo bit_no) const -> bool {
  return has_tbit(TBit(bit_no));
}

inline auto Gate::erase_bit(BitNo bit_no) -> size_t {
  return
    core_->get_cbits().erase(get_cbit(bit_no)) ||
    core_->get_tbits().erase(TBit(bit_no));
}

inline auto Gate::get_cbit_polarity(BitNo bit_no) const -> bool {
  assert(has_cbit(bit_no));
  return core_->get_cbits().count(CBit(bit_no, true));
}

inline auto Gate::is_controlled() const -> bool {
  return !core_->get_cbits().empty();
}

inline auto Gate::is_single_controlled() const -> bool {
  return core_->get_cbits().size() == 1u;
}

inline auto Gate::is_multi_controlled() const -> bool {
  return core_->get_cbits().size() > 1u;
}

inline auto Gate::is_single_target() const -> bool {
  return core_->get_tbits().size() == 1u;
}

inline auto Gate::is_multi_target() const -> bool {
  return core_->get_tbits().size() > 1u;
}

inline auto Gate::is_single_qubit_rotation() const -> bool {
  return !is_controlled() && is_single_target();
}

inline auto Gate::print(std::ostream& os) const -> void {
  core_->print(os);
}

inline auto Gate::get_gates() const -> Gates const& {
  return core_->get_gates();
}

inline auto Gate::get_gates() -> Gates& {
  return core_->get_gates();
}

inline Gate::Gate(std::unique_ptr<GateCore>&& core) : core_(std::move(core)) {}

inline Gate::Gate(GateCore*&& core) : core_(std::move(core)) {}
}
