/**
 * @file t.cpp
 * @brief implementation of T class
 */

#include "../t.hpp"

namespace qc {
const std::string T::TYPE_NAME = "T";
const Matrix T::TARGET_MATRIX =
  util::matrix::create(T::_createTargetMatrixList());
}
