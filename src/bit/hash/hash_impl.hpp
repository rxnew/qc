/**
 * @file hash_impl.hpp
 * @brief implementation header of hash for Bit class
 */

#pragma once

namespace std {
inline auto hash<qc::Bit>::operator()(const qc::Bit& obj) const -> size_t {
  return hash<unsigned short>()(static_cast<unsigned short>(obj.bitno_));
}

inline auto hash<qc::Tbit>::operator()(const qc::Tbit& obj) const -> size_t {
  return hash<unsigned short>()(static_cast<unsigned short>(obj.bitno_));
}
}
