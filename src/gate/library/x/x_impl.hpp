/**
 * @file x_impl.hpp
 * @brief implementation header of X class
 */

#pragma once

namespace qc {
inline auto X::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {0, 1, 1, 0};
}

template <class... Args>
X::X(Args&&... args) : Gate(std::forward<Args>(args)...) {
}

inline auto X::clone() const -> GatePtr {
  return GatePtr(new X(*this));
}

inline auto X::getTypeName() const -> const std::string& {
  return X::TYPE_NAME;
}

inline auto X::getTargetMatrix() const -> const Matrix& {
  return X::TARGET_MATRIX;
}
}
