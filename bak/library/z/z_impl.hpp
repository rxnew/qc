/**
 * @file z_impl.hpp
 * @brief implementation header of Z class
 */

#pragma once

namespace qc {
inline auto Z::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1, 0, 0, -1};
}

template <class... Args>
Z::Z(Args&&... args) : Gate(std::forward<Args>(args)...) {
}

inline auto Z::clone() const -> GatePtr {
  return GatePtr(new Z(*this));
}

inline auto Z::getTypeName() const -> const std::string& {
  return Z::TYPE_NAME;
}

inline auto Z::getTargetMatrix() const -> const Matrix& {
  return Z::TARGET_MATRIX;
}
}
