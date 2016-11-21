/**
 * @file hadamard.cpp
 * @brief implementation of Hadamard class
 */

#include "../hadamard.hpp"

namespace qc {
const std::string Hadamard::TYPE_NAME = "Hadamard";
const Matrix Hadamard::TARGET_MATRIX =
  util::matrix::create(Hadamard::_createTargetMatrixList());
}
