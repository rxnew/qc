/**
 * @file hadamard_impl.hpp
 * @brief implementation header of Hadamard class
 */

#pragma once

namespace qc {
inline auto Hadamard::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 1.0 / std::sqrt(2) + 0.0_i;
  return {a, a, a, -a};
}

template <class... Args>
Hadamard::Hadamard(Args&&... args) : Gate(std::forward<Args>(args)...) {
  assert(this->cbits_.empty());
  assert(static_cast<int>(this->tbits_.size()) == 1);
}

inline auto Hadamard::clone() const -> GatePtr {
  return GatePtr(new Hadamard(*this));
}

inline auto Hadamard::getTypeName() const -> const std::string& {
  return Hadamard::TYPE_NAME;
}

inline auto Hadamard::getTargetMatrix() const -> const Matrix& {
  return Hadamard::TARGET_MATRIX;
}
}
