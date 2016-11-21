#pragma once

namespace qc {
namespace util {
namespace string {
template <class T, int N, class Compare>
constexpr auto MultiValue<T, N, Compare>::operator==(T const& other) const
  -> bool {
  for(auto const& value : values_) {
    if(Compare()(value, other)) return true;
  }
  return false;
}

template <class T, int N, class Compare>
constexpr auto MultiValue<T, N, Compare>::operator!=(T const& other) const
  -> bool {
  return !(*this == other);
}
}
}
}
