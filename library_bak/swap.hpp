/**
 * @file swap.hpp
 * @brief header of Swap class
 */

#pragma once

#include "../../gate.hpp"

namespace qc {
class Swap : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Swap(Args&&... args);

  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
  auto computeMatrix(const std::set<Bitno>& bits) const -> Matrix;
  auto decompose() const -> GateList;
};
}

#include "swap/swap_impl.hpp"
