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
 * @brief control bit class
 */
class Cbit {
 public:
  Bitno bitno_;
  bool polarity_;
  Cbit();
  Cbit(Bitno bitno);
  Cbit(Bitno bitno, bool polarity);
  Cbit(const Cbit& other);
  Cbit(Cbit&&) noexcept = default;
  auto operator=(const Cbit& other) -> Cbit&;
  auto operator==(const Cbit& other) const -> bool;
  auto operator!=(const Cbit& other) const -> bool;
  auto operator<(const Cbit& other) const -> bool;
};

inline auto Cbit::operator==(const Cbit& other) const -> bool {
  return this->bitno_ == other.bitno_ && this->polarity_ == other.polarity_;
}

inline auto Cbit::operator!=(const Cbit& other) const -> bool {
  return !(*this == other);
}

/**
 * @brief target bit class
 */
class Tbit {
 public:
  Bitno bitno_;
  Tbit();
  Tbit(Bitno bitno);
  Tbit(const Tbit& other);
  Tbit(Tbit&&) noexcept = default;
  auto operator=(const Tbit& other) -> Tbit&;
  auto operator==(const Tbit& other) const -> bool;
  auto operator!=(const Tbit& other) const -> bool;
  auto operator<(const Tbit& other) const -> bool;
};

inline auto Tbit::operator=(const Tbit& other) -> Tbit& {
  this->bitno_ = other.bitno_;
  return *this;
}

inline auto Tbit::operator==(const Tbit& other) const -> bool{
  return this->bitno_ == other.bitno_;
}

inline auto Tbit::operator!=(const Tbit& other) const -> bool {
  return !(*this == other);
}

inline auto Tbit::operator<(const Tbit& other) const -> bool {
  return this->bitno_ < other.bitno_;
}

auto operator<<(std::ostream& os, const Cbit& obj) -> std::ostream&;
auto operator<<(std::ostream& os, const Tbit& obj) -> std::ostream&;

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
