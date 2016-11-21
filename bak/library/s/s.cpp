/**
 * @file s.cpp
 * @brief implementation of S class
 */

#include "../s.hpp"

namespace qc {
const std::string S::TYPE_NAME = "S";
const Matrix S::TARGET_MATRIX =
  util::matrix::create(S::_createTargetMatrixList());
}
