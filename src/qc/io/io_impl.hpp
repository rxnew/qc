/**
 * @file io_impl.hpp
 * @brief implementation header of qc::io methods
 */

#pragma once

namespace qc {
namespace io {
inline auto open(const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> Circuit {
  Circuit circuit;
  io::input(circuit, filename);
  return std::move(circuit);
}
}
}
