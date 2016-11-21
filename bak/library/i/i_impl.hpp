/**
 * @file i_impl.hpp
 * @brief implementation header of I class
 */

#pragma once

namespace qc {
inline auto I::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, 1.0 + 0.0_i};
}

template <class... Args>
I::I(Args&&... args) : Gate(std::forward<Args>(args)...) {
}

inline auto I::clone() const -> GatePtr {
  return GatePtr(new I(*this));
}

inline auto I::getTypeName() const -> const std::string& {
  return I::TYPE_NAME;
}

inline auto I::getTargetMatrix() const -> const Matrix& {
  return I::TARGET_MATRIX;
}
}
