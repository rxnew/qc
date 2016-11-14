/**
 * @file t.hpp
 * @brief header of T class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
class T : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  T(Args&&... args);

  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};
}

#include "t/t_impl.hpp"
