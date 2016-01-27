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
using Unitary = SparseMatrix<Complex>;

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
auto _createUnitary(const std::initializer_list<T>& list, const F& convert)
  -> Unitary {
  size_t size = std::sqrt(list.size());

  assert(list.size() == size * size);

  Unitary result(size, size);
  std::vector<Eigen::Triplet<Complex>> triplets;
  int index = 0;

  for(const auto& x : list) {
    int row = index % size;
    int col = index / size;
    auto val = convert(x);
    triplets.push_back(Eigen::Triplet<Complex>(row, col, val));
    index++;
  }

  result.setFromTriplets(triplets.begin(), triplets.end());

  return std::move(result);
}

template <class T>
inline auto createUnitary(const std::initializer_list<T>& list) -> Unitary {
  auto convert = [](const T& x) {return Complex(static_cast<Real>(x));};
  return _createUnitary(list, convert);
}

template <>
inline auto createUnitary<Complex>(const std::initializer_list<Complex>& list)
  -> Unitary {
  auto convert = [](const Complex& x) {return x;};
  return _createUnitary(list, convert);
}
}
}
