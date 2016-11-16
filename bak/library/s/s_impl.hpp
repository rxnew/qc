/**
 * @file s_impl.hpp
 * @brief implementation header of S class
 */

#pragma once

namespace qc {
inline auto S::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, 1.0_i};
}

template <class... Args>
S::S(Args&&... args) : Gate(std::forward<Args>(args)...) {
}

inline auto S::clone() const -> GatePtr {
  return GatePtr(new S(*this));
}

inline auto S::getTypeName() const -> const std::string& {
  return S::TYPE_NAME;
}

inline auto S::getTargetMatrix() const -> const Matrix& {
  return S::TARGET_MATRIX;
}
}
