#pragma once

#include <vector>
#include <complex>

#include "Eigen/Dense"

namespace util {
namespace eigen {
using Real = double;
using Complex = std::complex<Real>;
using Unitary = Eigen::Matrix<Complex, Eigen::Dynamic, Eigen::Dynamic>;

inline constexpr auto operator"" _i(long double val) -> Complex {
  return Complex(0, val);
}

template <class T>
inline auto createUnitary(const std::initializer_list<T>& list)
  -> Unitary {
  auto size = list.size() >> 1;
  std::vector<Complex> v;
  for(const auto& x : list) {
    v.push_back(static_cast<Real>(x) + 0.0_i);
  }
  return Unitary(Eigen::Map<Unitary>(v.data(), size, size));
}

template <>
inline auto createUnitary<Complex>(const std::initializer_list<Complex>& list)
  -> Unitary {
  auto size = list.size() >> 1;
  return Unitary(Eigen::Map<Unitary>(std::vector<Complex>(list).data(), \
                                     size, size));
}
}
}
