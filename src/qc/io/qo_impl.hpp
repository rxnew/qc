/**
 * @file qo_impl.hpp
 * @brief implementation header of qc::io::Qo class
 */

#pragma once

namespace qc {
namespace io {
inline auto Qo::open(const std::string& filename)
  throw(IfExc, std::ios_base::failure) -> Circuit {
  Circuit circuit;
  Qo::input(circuit, filename);
  return std::move(circuit);
}
}
}
