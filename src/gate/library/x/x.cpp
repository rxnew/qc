/**
 * @file x.cpp
 * @brief implementation of X class
 */

#include "../x.hpp"

namespace qc {
const std::string X::TYPE_NAME = "X";
const Matrix X::TARGET_MATRIX =
  util::matrix::create(X::_createTargetMatrixList());
}
