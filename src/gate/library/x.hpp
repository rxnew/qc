/**
 * @file x.hpp
 * @brief header of X class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
class X : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  X(Args&&... args);

  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};
}

#include "x/x_impl.hpp"
