/**
 * @file gate_impl.hpp
 * @brief implementation header of quantum gate classes
 */

#pragma once

namespace qc {
inline Gate::Impl::Impl(TBit const& tbit) : tbits_{tbit} {}

inline Gate::Impl::Impl(CBit const& cbit, TBit const& tbit)
  : cbits_{cbit}, tbits_{tbit} {
}

inline Gate::Impl::Impl(CBit const& cbit, const TBits& tbits)
  : cbits_{cbit}, tbits_(tbits) {
}

inline Gate::Impl::Impl(CBit const& cbit, TBits&& tbits)
  : cbits_{cbit}, tbits_(std::move(tbits)) {
}

inline Gate::Impl::Impl(const CBits& cbits, TBit const& tbit) :
  cbits_(cbits), tbits_{tbit} {
}

inline Gate::Impl::Impl(CBits&& cbits, TBit const& tbit) :
  cbits_(std::move(cbits)), tbits_{tbit} {
}

inline Gate::Impl::Impl(const CBits& cbits, const TBits& tbits) :
  cbits_(cbits), tbits_(tbits) {
}

inline Gate::Impl::Impl(CBits&& cbits, TBits&& tbits) :
  cbits_(std::move(cbits)), tbits_(std::move(tbits)) {
}

template <class... Args>
inline Gate::Impl::Impl(Args&&... args) {
  _add_bit(std::forward<Args>(args)...);
}

inline auto Gate::Impl::operator==(Impl const& other) const -> bool {
  return
    std::is_same<decltype(*this), decltype(other)>::value &&
    cbits_ == other.cbits_ && tbits_ == other.tbits_;
}

inline auto Gate::Impl::operator!=(Impl const& other) const -> bool {
  return !(*this == other);
}

inline auto Gate::Impl::get_cbits() const -> const CBits& {
  return cbits_;
}

inline auto Gate::Impl::get_tbits() const -> const TBits& {
  return tbits_;
}

inline auto Gate::Impl::_add_bit(CBit const& cbit) -> void {
  cbits_.insert(cbit);
}

inline auto Gate::Impl::_add_bit(TBit const& tbit) -> void {
  tbits_.insert(tbit);
}

template <class BitT, class... Args>
inline auto Gate::Impl::_add_bit(BitT&& bit, Args&&... args) -> void {
  _add_bit(std::forward<BitT>(bit));
  _add_bit(std::forward<BitT>(args)...);
}
}
