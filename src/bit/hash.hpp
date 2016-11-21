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
  auto operator()(qc::Bit const& obj) const -> size_t;
};

template <>
struct hash<qc::CBit> {
  auto operator()(qc::CBit const& obj) const -> size_t;
};

template <>
struct hash<qc::TBit> {
  auto operator()(qc::TBit const& obj) const -> size_t;
};
}

#include "hash/hash_impl.hpp"
