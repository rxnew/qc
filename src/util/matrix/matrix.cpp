#include "../matrix.hpp"

namespace qc {
namespace util {
namespace matrix {
auto identity(size_t size) -> Matrix {
  Matrix result(size, size);
  for(size_t i = 0; i < size; i++) {
    result.insert(i, i) = Complex(1);
  }
  return std::move(result);
}
}
}
}
