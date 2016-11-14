/**
 * @file swap_impl.hpp
 * @brief implementation header of Swap class
 */

#pragma once

namespace qc {
inline auto Swap::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1, 0, 0, 0, \
          0, 0, 1, 0, \
          0, 1, 0, 0, \
          0, 0, 0, 1};
}

template <class... Args>
Swap::Swap(Args&&... args) : Gate(std::forward<Args>(args)...) {
  assert(static_cast<int>(this->tbits_.size()) == 2);
}

inline auto Swap::clone() const -> GatePtr {
  return GatePtr(new Swap(*this));
}

inline auto Swap::getTypeName() const -> const std::string& {
  return Swap::TYPE_NAME;
}

inline auto Swap::getTargetMatrix() const -> const Matrix& {
  return Swap::TARGET_MATRIX;
}
}
