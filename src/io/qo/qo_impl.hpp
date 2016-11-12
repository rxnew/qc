/**
 * @file qo_impl.hpp
 * @brief implementation header of qc::io::Qo class
 */

#pragma once

namespace qc {
namespace io {
inline auto Qo::print(const Circuit& circuit, std::ostream& os) -> void {
  circuit.print(os);
}
}
}
