#pragma once

namespace qc {
namespace util {
namespace math {
template <class T, class U>
auto pow(T x, U n) -> T;
}
}
}

#include "math/math_impl.hpp"
