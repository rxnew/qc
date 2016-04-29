/**
 * @file bit_impl.hpp
 * @brief implementation header of Cbit and Tbit class
 */

#pragma once

namespace qc {
inline Bit::Bit() : bitno_(0) {
}

inline Bit::Bit(Bitno bitno) : bitno_(bitno) {
}

inline Bit::Bit(const Bit& other) : bitno_(other.bitno_) {
}

inline Bit::~Bit() {
}

inline auto Bit::operator=(const Bit& other) -> Bit& {
  this->bitno_ = other.bitno_;
  return *this;
}

inline auto Bit::operator=(Bit&& other) -> Bit& {
  return this->operator=(other);
}

inline auto Bit::operator==(const Bit& other) const -> bool{
  return this->bitno_ == other.bitno_;
}

inline auto Bit::operator!=(const Bit& other) const -> bool {
  return !(*this == other);
}

inline auto Bit::operator<(const Bit& other) const -> bool {
  return this->bitno_ < other.bitno_;
}

template <class... Args>
inline Cbit::Cbit(Args&&... args)
  : Bit(std::forward<Args>(args)...), polarity_(true) {
}

inline Cbit::Cbit(Bitno bitno, bool polarity)
  : Bit(bitno), polarity_(polarity) {
}

inline Cbit::Cbit(const Cbit& other)
  : Bit(other.bitno_), polarity_(other.polarity_) {
}

inline auto Cbit::operator=(const Cbit& other) -> Cbit& {
  this->bitno_ = other.bitno_;
  this->polarity_ = other.polarity_;
  return *this;
}

inline auto Cbit::operator=(Cbit&& other) -> Cbit& {
  return this->operator=(other);
}

inline auto Cbit::operator==(const Cbit& other) const -> bool {
  return Bit::operator==(other) && this->polarity_ == other.polarity_;
}

inline auto Cbit::operator!=(const Cbit& other) const -> bool {
  return !(*this == other);
}

inline auto Cbit::operator<(const Cbit& other) const -> bool {
  return this->bitno_ == other.bitno_ ? \
    !this->polarity_ : Bit::operator<(other);
}

template <class... Args>
inline Tbit::Tbit(Args&&... args) : Bit(std::forward<Args>(args)...) {
}

inline auto operator<<(std::ostream& os, const Cbit& obj) -> std::ostream& {
  char sign = obj.polarity_ ? '\0' : '!';
  return os << sign << obj.bitno_;
}

inline auto operator<<(std::ostream& os, const Tbit& obj) -> std::ostream& {
  return os << 'T' << obj.bitno_;
}
}

namespace std {
inline auto hash<qc::Tbit>::operator()(const qc::Tbit& obj) const -> size_t {
  return hash<unsigned short>()(static_cast<unsigned short>(obj.bitno_));
}
}
