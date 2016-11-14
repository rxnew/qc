/**
 * @file bit.hpp
 * @brief header of the control and target bit class
 */

#pragma once

#include <iostream>
#include <utility>

namespace qc {
/**
 * @brief bit class
 */
class Bit {
 public:
  using No = unsigned int;

  explicit Bit(No no);
  Bit(Bit const&) = default;
  Bit(Bit&&) noexcept = default;

  virtual ~Bit() = default;

  auto operator=(Bit const&) -> Bit& = default;
  auto operator=(Bit&&) -> Bit& = default;
  auto operator==(Bit const& other) const -> bool;
  auto operator!=(Bit const& other) const -> bool;
  auto operator<(Bit const& other) const -> bool;
  auto operator>(Bit const& other) const -> bool;

  auto get_no() const -> No;

 protected:
  No no_;
};

/**
 * @brief control bit class
 */
class CBit : public Bit {
 public:
  explicit CBit(No no, bool polarity = true);
  CBit(CBit const& other) = default;
  CBit(CBit&&) noexcept = default;

  ~CBit() = default;

  auto operator=(CBit const&) -> CBit& = default;
  auto operator=(CBit&&) -> CBit& = default;
  auto operator==(CBit const& other) const -> bool;
  auto operator!=(CBit const& other) const -> bool;
  auto operator<(CBit const& other) const -> bool;
  auto operator>(CBit const& other) const -> bool;

  auto get_polarity() const -> bool;
  auto invert_polarity() -> bool;

 private:
  bool polarity_;
};

/**
 * @brief target bit class
 */
class TBit : public Bit {
 public:
  template <class... Args>
  TBit(Args&&... args);

  ~TBit() = default;
};

auto operator<<(std::ostream& os, Bit const& obj) -> std::ostream&;
auto operator<<(std::ostream& os, CBit const& obj) -> std::ostream&;
auto operator<<(std::ostream& os, TBit const& obj) -> std::ostream&;

auto operator"" _bit(unsigned long long bit_no_i) -> Bit::No;
}

#include "bit/bit_impl.hpp"
