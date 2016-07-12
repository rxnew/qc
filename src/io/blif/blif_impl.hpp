/**
 * @file blif_impl.hpp
 * @brief implementation header of qc::io::Blif class
 */

#pragma once

#include "../../algorithm/oracle.hpp"

namespace qc {
namespace io {
inline auto Blif::print(const Circuit& circuit, std::ostream& os) -> void {
  assert(qc::isMctCircuit(circuit));
  Blif::_print(circuit, os);
}
}
}
