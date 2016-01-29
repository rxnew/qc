#pragma once

#include <vector>

#include "sprout/complex.hpp"
#include "Eigen/Dense"
#include "Eigen/Sparse"

namespace util {
namespace eigen {
using sprout::udl::complex::operator"" _i;
using Eigen::SparseMatrix;

using Real = double;
using Complex = sprout::complex<Real>;
using Matrix = SparseMatrix<Complex>;

auto identity(size_t size) -> Matrix;

auto identity() -> Matrix;

template <int>
auto braket() -> Matrix;

template <>
auto braket<0>() -> Matrix;

template <>
auto braket<1>() -> Matrix;

template <class T>
auto tensor(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs)
  -> SparseMatrix<T>;

template <class T>
inline auto create(const std::initializer_list<T>& list) -> Matrix;

template <>
inline auto create<Complex>(const std::initializer_list<Complex>& list)
  -> Matrix;

// Private methods
template <class T, class F>
auto _create(const std::initializer_list<T>& list, const F& convert)
  -> Matrix;

// Implementations
auto identity(size_t size) -> Matrix {
  Matrix result(size, size);
  for(size_t i = 0; i < size; i++) {
    result.insert(i, i) = Complex(1);
  }
  return std::move(result);
}

inline auto identity() -> Matrix {
  return identity(2);
}

template <>
inline auto braket<0>() -> Matrix {
  return create({1, 0, 0, 0});
}

template <>
inline auto braket<1>() -> Matrix {
  return create({0, 0, 0, 1});
}

template <class T>
auto tensor(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs)
  -> SparseMatrix<T> {
  SparseMatrix<T> result(lhs.rows() * rhs.rows(), lhs.cols() * rhs.cols());

  for(int i = 0; i < lhs.outerSize(); i++) {
    for(typename SparseMatrix<T>::InnerIterator it(lhs, i); it; ++it) {
      int row = it.row() * rhs.rows();
      int col = it.col() * rhs.cols();
      for(int j = 0; j < rhs.outerSize(); j++) {
        for(typename SparseMatrix<T>::InnerIterator jt(rhs, j); jt; ++jt) {
          result.insert(row + jt.row(), col + jt.col()) = \
            it.value() * jt.value();
        }
      }
    }
  }

  return std::move(result);
}

template <class T, class F>
auto _create(const std::initializer_list<T>& list, const F& convert)
  -> Matrix {
  size_t size = std::sqrt(list.size());

  assert(list.size() == size * size);

  Matrix result(size, size);
  int index = 0;

  for(const auto& x : list) {
    auto val = convert(x);
    if(val == 0.0_i) continue;
    int row = index % size;
    int col = index / size;
    result.insert(row, col) = val;
    index++;
  }

  return std::move(result);
}

template <class T>
inline auto create(const std::initializer_list<T>& list) -> Matrix {
  auto convert = [](const T& x) {return Complex(static_cast<Real>(x));};
  return _create(list, convert);
}

template <>
inline auto create<Complex>(const std::initializer_list<Complex>& list)
  -> Matrix {
  auto convert = [](const Complex& x) {return x;};
  return _create(list, convert);
}
}
}
