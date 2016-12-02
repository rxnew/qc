#pragma once

namespace qc {
inline auto GateKernel::operator==(GateKernel const& other) const -> bool {
  return get_type() == other.get_type() && is_dagger() == other.is_dagger();
}

inline auto GateKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}
}
