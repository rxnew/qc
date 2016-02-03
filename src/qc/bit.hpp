/**
 * @file bit.hpp
 * @brief header of the control and target bit class
 */

#pragma once

#include <iostream>
#include <cassert>

namespace qc {
using Bitno = unsigned short;
/**
 * @brief target bit class
 */
class Bit {
 public:
  Bitno bitno_;

  Bit();
  Bit(Bitno bitno);
  Bit(const Bit& other);
  Bit(Bit&&) noexcept = default;
  virtual ~Bit();
  auto operator=(const Bit& other) -> Bit&;
  auto operator==(const Bit& other) const -> bool;
  auto operator!=(const Bit& other) const -> bool;
  auto operator<(const Bit& other) const -> bool;
};

/**
 * @brief control bit class
 */
class Cbit : public Bit {
 public:
  bool polarity_;
  template <class... Args>
  Cbit(Args&&... args);
  Cbit(Bitno bitno, bool polarity);
  Cbit(const Cbit& other);
  Cbit(Cbit&&) noexcept = default;
  auto operator=(const Cbit& other) -> Cbit&;
  auto operator==(const Cbit& other) const -> bool;
  auto operator!=(const Cbit& other) const -> bool;
  auto operator<(const Cbit& other) const -> bool;
};

/**
 * @brief target bit class
 */
class Tbit : public Bit {
 public:
  template <class... Args>
  Tbit(Args&&... args);
};

auto operator<<(std::ostream& os, const Cbit& obj) -> std::ostream&;
auto operator<<(std::ostream& os, const Tbit& obj) -> std::ostream&;

// implementation
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
inline Cbit::Cbit(Args&&... args) : Bit(args...), polarity_(true) {
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
inline Tbit::Tbit(Args&&... args) : Bit(args...) {
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
template <>
struct hash<qc::Cbit> {
  auto operator()(const qc::Cbit& obj) const -> size_t {
    auto bitno = obj.bitno_;
    if(!obj.polarity_) {
      decltype(bitno) mask = 1 << (8 * sizeof(decltype(bitno)) - 1);
      bitno ^= mask;
    }
    return hash<unsigned short>()(static_cast<unsigned short>(bitno));
  }
};

template <>
struct hash<qc::Tbit> {
  auto operator()(const qc::Tbit& obj) const -> size_t {
    return hash<unsigned short>()(static_cast<unsigned short>(obj.bitno_));
  }
};
}
