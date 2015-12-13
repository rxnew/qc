/**
 * @file bit.hpp
 * @brief header of the control and target bit class
 */

#pragma once

#include <iostream>
#include <cassert>

#include "container_helper.hpp"

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
  Cbit& operator=(const Cbit& other);
  bool operator==(const Cbit& other) const;
  bool operator!=(const Cbit& other) const;
  bool operator<(const Cbit& other) const;
};

/**
 * @brief target bit class
 */
class Tbit {
 public:
  Bitno bitno_;
  Tbit();
  Tbit(Bitno bitno);
  Tbit(const Tbit& other);
  Tbit& operator=(const Tbit& other);
  bool operator==(const Tbit& other) const;
  bool operator!=(const Tbit& other) const;
  bool operator<(const Tbit& other) const;
};

std::ostream& operator<<(std::ostream& os, const Cbit& obj);
std::ostream& operator<<(std::ostream& os, const Tbit& obj);
}

namespace std {
template <>
struct hash<qc::Cbit> {
  size_t operator()(const qc::Cbit& obj) const {
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
  size_t operator()(const qc::Tbit& obj) const {
    return hash<unsigned short>()(static_cast<unsigned short>(obj.bitno_));
  }
};
}
