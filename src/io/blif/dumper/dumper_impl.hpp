/**
 * @file dumper_impl.hpp
 * @brief implementation header of Blif::Dumper class
 */

#pragma once

namespace qc {
namespace io {
inline Blif::Dumper::Dumper(const Circuit& circuit,
                            std::ostream& os) : circuit_(&circuit), os_(&os) {}
}
}
