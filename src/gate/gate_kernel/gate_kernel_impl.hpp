#pragma once

namespace qc {
inline auto GateKernel::operator==(GateKernel const& other) const -> bool {
  return get_type_name() == other.get_type_name();
}

inline auto GateKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}
}
