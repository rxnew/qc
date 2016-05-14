/**
 * @file bit.hpp
 * @brief header of the control and target bit class
 */

#pragma once

#include <iostream>
#include <utility>
#include <cassert>

namespace qc {
using Bitno = unsigned short;
/**
 * @brief target bit class
 */
class Bit {
 public:
  Bitno bitno_;

  explicit Bit(Bitno bitno);
  Bit(const Bit&) = default;
  Bit(Bit&&) noexcept = default;
  virtual ~Bit() = default;

  auto operator=(const Bit&) -> Bit& = default;
  auto operator=(Bit&&) -> Bit& = default;
  auto operator==(const Bit& other) const -> bool;
  auto operator!=(const Bit& other) const -> bool;
  auto operator<(const Bit& other) const -> bool;
  auto operator>(const Bit& other) const -> bool;
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
  Cbit(const Cbit& other) = default;
  Cbit(Cbit&&) noexcept = default;

  auto operator=(const Cbit&) -> Cbit& = default;
  auto operator=(Cbit&&) -> Cbit& = default;
  auto operator==(const Cbit& other) const -> bool;
  auto operator!=(const Cbit& other) const -> bool;
  auto operator<(const Cbit& other) const -> bool;
  auto operator>(const Cbit& other) const -> bool;
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
}

namespace std {
template <>
struct hash<qc::Cbit> {
  auto operator()(const qc::Cbit& obj) const -> size_t;
};

template <>
struct hash<qc::Tbit> {
  auto operator()(const qc::Tbit& obj) const -> size_t;
};
}

#include "bit/bit_impl.hpp"
