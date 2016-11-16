/**
 * @file hadamard.hpp
 * @brief header of Hadamard class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
class Hadamard : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Hadamard(Args&&... args);

  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};
}

#include "hadamard/hadamard_impl.hpp"
