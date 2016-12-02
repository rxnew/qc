/**
 * @file bit_impl.hpp
 * @brief implementation header of Cbit and Tbit class
 */

#pragma once

namespace qc {
inline Bit::Bit(No no) : no_(no) {}

inline auto Bit::operator==(Bit const& other) const -> bool {
  return no_ == other.no_;
}

inline auto Bit::operator!=(Bit const& other) const -> bool {
  return !(*this == other);
}

inline auto Bit::operator<(Bit const& other) const -> bool {
  return no_ < other.no_;
}

inline auto Bit::operator>(Bit const& other) const -> bool {
  return !(*this < other) && *this != other;
}

inline auto Bit::get_no() const -> No {
  return no_;
}

inline CBit::CBit(No no, bool polarity) : Bit(no), polarity_(polarity) {}

inline auto CBit::operator==(CBit const& other) const -> bool {
  return Bit::operator==(other) && polarity_ == other.polarity_;
}

inline auto CBit::operator!=(CBit const& other) const -> bool {
  return !(*this == other);
}

inline auto CBit::operator<(CBit const& other) const -> bool {
  return
    Bit::operator==(other) ?
    polarity_ && !other.polarity_ : Bit::operator<(other);
}

inline auto CBit::operator>(CBit const& other) const -> bool {
  return !(*this < other) && *this != other;
}

inline auto CBit::operator!() const -> CBit {
  return CBit(no_, !polarity_);
}

inline auto CBit::get_polarity() const -> bool {
  return polarity_;
}

inline auto CBit::invert_polarity() -> bool {
  return polarity_ ^= true;
}

template <class... Args>
inline TBit::TBit(Args&&... args) : Bit(std::forward<Args>(args)...) {}

inline auto operator<<(std::ostream& os, Bit const& obj) -> std::ostream& {
  return os << obj.get_no();
}

inline auto operator<<(std::ostream& os, CBit const& obj) -> std::ostream& {
  if(!obj.get_polarity()) os << '!';
  return os << obj.get_no();
}

inline auto operator<<(std::ostream& os, TBit const& obj) -> std::ostream& {
  return os << 'T' << obj.get_no();
}

inline namespace literals {
inline namespace bit_literals {
inline auto operator"" _bit(unsigned long long bit_no_i) -> Bit::No {
  return static_cast<Bit::No>(bit_no_i);
}

inline auto operator"" _cbit(unsigned long long bit_no_i) -> CBit {
  return CBit(static_cast<Bit::No>(bit_no_i));
}

inline auto operator"" _tbit(unsigned long long bit_no_i) -> TBit {
  return TBit(static_cast<Bit::No>(bit_no_i));
}
}
}
}
