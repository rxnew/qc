#pragma once

namespace qc {
inline auto GatesWrapper::get_gates() const -> Gates const& {
  return gates_;
}

inline auto GatesWrapper::get_gates() -> Gates& {
  return gates_;
}
}
