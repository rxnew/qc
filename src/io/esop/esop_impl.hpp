/**
 * @file esop_impl.hpp
 * @brief implementation header of qc::io::Esop class
 */

#pragma once

#include "../../algorithm/oracle.hpp"

namespace qc {
namespace io {
inline auto Esop::_isCommentLine(const std::string& line) -> bool {
  return line.front() == '#';
}

inline auto Esop::_isEndLine(const std::string& line) -> bool {
  return line == ".e";
}

inline auto Esop::open(const std::string& filename)
  throw(IfExc, std::ios_base::failure) -> Circuit {
  Circuit circuit;
  Esop::input(circuit, filename);
  return std::move(circuit);
}

inline auto Esop::print(const Circuit& circuit, std::ostream& os) -> void {
  assert(qc::isEsopCircuit(circuit));
  Esop::_print(circuit, os);
}
}
}
