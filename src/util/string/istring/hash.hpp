#pragma once

#include "../istring.hpp"

namespace std {
template <>
struct hash<qc::util::string::istring> {
  using istring = qc::util::string::istring;
  auto operator()(const istring& obj) const -> size_t;
};
}

#include "hash/hash_impl.hpp"
