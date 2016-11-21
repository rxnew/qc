/**
 * @file v.cpp
 * @brief implementation of V and VPlus class
 */

#include "../v.hpp"

namespace qc {
const std::string V::TYPE_NAME = "V";
const Matrix V::TARGET_MATRIX =
  util::matrix::create(V::_createTargetMatrixList());

const std::string VPlus::TYPE_NAME = "VPlus";
const Matrix VPlus::TARGET_MATRIX =
  util::matrix::create(VPlus::_createTargetMatrixList());
}
