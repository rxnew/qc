/**
 * @file u.hpp
 * @brief header of U class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
class U : public Gate {
 private:
  const Matrix target_matrix_;

 public:
  static const std::string TYPE_NAME;

  template <class... Args>
  U(const Matrix& target_matrix, Args&&... args);
  U(const U&) = default;
  U(U&&) = default;

  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};
}

#include "u/u_impl.hpp"
