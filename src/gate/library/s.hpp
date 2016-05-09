/**
 * @file s.hpp
 * @brief header of S class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
class S : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  S(Args&&... args);

  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};
}

#include "s/s_impl.hpp"
