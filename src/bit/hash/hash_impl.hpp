/**
 * @file hash_impl.hpp
 * @brief implementation header of hash for Bit class
 */

#pragma once

namespace std {
inline auto hash<qc::Bit>::operator()(qc::Bit const& obj) const -> size_t {
  return hash<qc::Bit::No>()(obj.get_no());
}

inline auto hash<qc::CBit>::operator()(qc::CBit const& obj) const -> size_t {
  auto constexpr const mask =
    static_cast<size_t>(1) << ((sizeof(size_t) << 3) - 1);
  return hash<qc::Bit::No>()(obj.get_no()) ^ (obj.get_polarity() ? 0 : mask);
}

inline auto hash<qc::TBit>::operator()(qc::TBit const& obj) const -> size_t {
  return hash<qc::Bit::No>()(obj.get_no());
}
}
