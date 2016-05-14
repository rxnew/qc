/**
 * @file hash.hpp
 * @brief header of hash for Bit class
 */

#pragma once

#include <functional>

#include "../bit.hpp"

namespace std {
template <>
struct hash<qc::Bit> {
  auto operator()(const qc::Bit& obj) const -> size_t;
};

template <>
struct hash<qc::Cbit> {
  auto operator()(const qc::Cbit& obj) const -> size_t;
};

template <>
struct hash<qc::Tbit> {
  auto operator()(const qc::Tbit& obj) const -> size_t;
};
}

#include "hash/hash_impl.hpp"
