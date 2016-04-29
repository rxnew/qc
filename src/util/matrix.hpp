#pragma once

#include <vector>

#include "sprout/complex.hpp"
#include "Eigen/Dense"
#include "Eigen/Sparse"

namespace util {
namespace matrix {
using sprout::udl::complex::operator"" _i;
using Eigen::SparseMatrix;

using Real = double;
using Complex = sprout::complex<Real>;
using Matrix = SparseMatrix<Complex>;
using Vector = Eigen::Matrix<Complex, Eigen::Dynamic, 1>;

auto identity(size_t size) -> Matrix;

auto identity() -> Matrix;

template <int>
auto ketbra() -> Matrix;

template <>
auto ketbra<0>() -> Matrix;

template <>
auto ketbra<1>() -> Matrix;

template <class T>
auto create(const std::initializer_list<T>& list) -> Matrix;

template <>
auto create<Complex>(const std::initializer_list<Complex>& list)
  -> Matrix;

static const Vector Y_STATE;
static const Vector A_STATE;

template <int>
auto ket() -> Vector;

template <>
auto ket<0>() -> Vector;

template <>
auto ket<1>() -> Vector;

template <>
auto ket<'+'>() -> Vector;

template <>
auto ket<'-'>() -> Vector;

template <>
auto ket<'Y'>() -> Vector;

template <>
auto ket<'A'>() -> Vector;

auto createVector(std::vector<Complex>&& vec) -> Vector;

template <class T>
auto tensor(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs)
  -> SparseMatrix<T>;

template <class T, int R, int C>
auto tensor(const Eigen::Matrix<T, R, C>& lhs, \
            const Eigen::Matrix<T, R, C>& rhs) -> Eigen::Matrix<T, R, C>;

// Private methods
template <class T, class F>
auto _create(const std::initializer_list<T>& list, const F& convert)
  -> Matrix;

// Implementations
inline auto identity() -> Matrix {
  return identity(2);
}

template <>
inline auto ketbra<0>() -> Matrix {
  return create({1, 0, 0, 0});
}

template <>
inline auto ketbra<1>() -> Matrix {
  return create({0, 0, 0, 1});
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
    if(val != 0.0_i) {
      int row = index % size;
      int col = index / size;
      result.insert(row, col) = val;
    }
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

template <>
inline auto ket<0>() -> Vector {
  return createVector({1.0 + 0.0_i, 0.0_i});
}

template <>
inline auto ket<1>() -> Vector {
  return createVector({0.0_i, 1.0 + 0.0_i});
}

template <>
inline auto ket<'+'>() -> Vector {
  return createVector({std::sqrt(2.0) / 2.0 + 0.0_i, \
        std::sqrt(2.0) / 2.0 + 0.0_i});
}

template <>
inline auto ket<'-'>() -> Vector {
  return createVector({std::sqrt(2.0) / 2.0 + 0.0_i, \
        std::sqrt(2.0) / -2.0 + 0.0_i});
}

template <>
inline auto ket<'Y'>() -> Vector {
  return createVector\
    ({std::sqrt(2.0) / 2.0 + 0.0_i, std::sqrt(2.0) / 2.0 * 1.0_i});
}

template <>
inline auto ket<'A'>() -> Vector {
  return createVector\
    ({std::sqrt(2.0) / 2.0 + 0.0_i, \
        std::sqrt(2.0) / 2.0 * sprout::exp(std::atan(1.0) * 1.0_i)});
}

inline auto createVector(std::vector<Complex>&& vec) -> Vector {
  return Vector(Eigen::Map<Vector>(vec.data(), vec.size()));
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

template <class T, int R, int C>
auto tensor(const Eigen::Matrix<T, R, C>& lhs, \
            const Eigen::Matrix<T, R, C>& rhs) -> Eigen::Matrix<T, R, C> {
  Eigen::Matrix<T, R, C> \
    result(lhs.rows() * rhs.rows(), lhs.cols() * rhs.cols());

  for(int ir = 0; ir < lhs.rows(); ir++) {
    for(int ic = 0; ic < lhs.cols(); ic++) {
      if(lhs(ir, ic) == T(0)) continue;
      int row = ir * rhs.rows();
      int col = ic * rhs.cols();
      for(int jr = 0; jr < rhs.rows(); jr++) {
        for(int jc = 0; jc < rhs.cols(); jc++) {
          result(row + jr, col + jc) = lhs(ir, ic) * rhs(jr, jc);
        }
      }
    }
  }

  return std::move(result);
}
}
}
