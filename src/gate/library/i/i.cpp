/**
 * @file i.cpp
 * @brief implementation of I class
 */

#include "../i.hpp"

namespace qc {
const std::string I::TYPE_NAME = "I";
const Matrix I::TARGET_MATRIX =
  util::matrix::create(I::_createTargetMatrixList());
}
