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
}
}

#include "matrix_impl.hpp"
