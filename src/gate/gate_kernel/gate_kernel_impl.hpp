#pragma once

namespace qc {
inline auto GateKernel::operator==(GateKernel const& other) const -> bool {
  return get_type() == other.get_type() && be_daggered() == other.be_daggered();
}

inline auto GateKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}
}
