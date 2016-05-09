/**
 * @file u_impl.hpp
 * @brief implementation header of U class
 */

#pragma once

namespace qc {
template <class... Args>
U::U(const Matrix& target_matrix, Args&&... args)
  : target_matrix_(target_matrix), Gate(std::forward<Args>(args)...) {
}

inline auto U::clone() const -> GatePtr {
  return GatePtr(new U(*this));
}

inline auto U::getTypeName() const -> const std::string& {
  return U::TYPE_NAME;
}

inline auto U::getTargetMatrix() const -> const Matrix& {
  return this->target_matrix_;
}
}
