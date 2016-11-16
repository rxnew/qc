/**
 * @file t_impl.hpp
 * @brief implementation header of T class
 */

#pragma once

namespace qc {
inline auto T::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, sprout::exp(std::atan(1.0) * 1.0_i)};
}

template <class... Args>
T::T(Args&&... args) : Gate(std::forward<Args>(args)...) {
}

inline auto T::clone() const -> GatePtr {
  return GatePtr(new T(*this));
}

inline auto T::getTypeName() const -> const std::string& {
  return T::TYPE_NAME;
}

inline auto T::getTargetMatrix() const -> const Matrix& {
  return T::TARGET_MATRIX;
}
}
