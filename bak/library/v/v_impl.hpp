/**
 * @file v_impl.hpp
 * @brief implementation header of V and VPlus class
 */

#pragma once

namespace qc {
inline auto V::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 0.5 + 0.5_i;
  constexpr auto b = 0.5 - 0.5_i;
  return {a, b, b, a};
}

template <class... Args>
V::V(Args&&... args) : Gate(std::forward<Args>(args)...) {
}

inline auto V::clone() const -> GatePtr {
  return GatePtr(new V(*this));
}

inline auto V::getTypeName() const -> const std::string& {
  return V::TYPE_NAME;
}

inline auto V::getTargetMatrix() const -> const Matrix& {
  return V::TARGET_MATRIX;
}

inline auto VPlus::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 0.5 + 0.5_i;
  constexpr auto b = 0.5 - 0.5_i;
  return {b, a, a, b};
}

template <class... Args>
VPlus::VPlus(Args&&... args) : Gate(std::forward<Args>(args)...) {
}

inline auto VPlus::clone() const -> GatePtr {
  return GatePtr(new VPlus(*this));
}

inline auto VPlus::getTypeName() const -> const std::string& {
  return VPlus::TYPE_NAME;
}

inline auto VPlus::getTargetMatrix() const -> const Matrix& {
  return VPlus::TARGET_MATRIX;
}
}
