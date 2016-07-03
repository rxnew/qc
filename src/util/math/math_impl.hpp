#pragma once

namespace qc {
namespace util {
namespace math {
template <class T, class U>
auto pow(T x, U n) -> T {
  if(!n) return 1;
  auto res = math::pow(x * x, n / 2);
  return n % 2 ? res * x : res;
}
}
}
}
