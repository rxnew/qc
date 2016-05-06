/**
 * @file bit.cpp
 * @brief implementation of the control and target bit class
 */

#include "../bit.hpp"

namespace std {
auto hash<qc::Cbit>::operator()(const qc::Cbit& obj) const -> size_t {
  auto bitno = obj.bitno_;
  if(!obj.polarity_) {
    decltype(bitno) mask = 1 << (8 * sizeof(decltype(bitno)) - 1);
    bitno ^= mask;
  }
  return hash<unsigned short>()(static_cast<unsigned short>(bitno));
}
}
