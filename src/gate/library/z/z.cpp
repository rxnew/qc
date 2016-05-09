/**
 * @file z.cpp
 * @brief implementation of Z class
 */

#include "../z.hpp"

namespace qc {
const std::string Z::TYPE_NAME = "Z";
const Matrix Z::TARGET_MATRIX =
  util::matrix::create(Z::_createTargetMatrixList());
}
