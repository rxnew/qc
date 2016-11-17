#pragma once

namespace qc {
namespace util {
namespace string {
template <class T, int N, class Compare = std::equal_to<T>>
class MultiValue {
 public:
  constexpr auto operator==(T const& other) const -> bool;
  constexpr auto operator!=(T const& other) const -> bool;

  std::array<T, N> const values_;
};
}
}
}

#include "multi_value/multi_value_impl.hpp"
