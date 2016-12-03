#pragma once

namespace qc {
inline auto GateKernel::operator==(GateKernel const& other) const -> bool {
  return get_type() == other.get_type() && bedaggered() == other.bedaggered();
}

inline auto GateKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}
}
