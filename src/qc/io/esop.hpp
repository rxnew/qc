/**
 * @file esop.hpp
 * @brief header of Esop class
 */

#pragma once

#include <fstream>

#include "../circuit.hpp"
#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
class Esop {
 private:
  using IfExc = exc::IllegalFormatException;
  using Counts = std::map<std::string, size_t>;

  static std::array<std::string, 2> _err_msgs;

  static auto _isCommentLine(const std::string& line) -> bool;
  static auto _isEndLine(const std::string& line) -> bool;
  static auto _setCount(Counts& counts, const std::string& line)
    throw(IfExc) -> void;
  static auto _getCounts(std::ifstream& ifs)
    throw(IfExc) -> Counts;
  static auto _getCbits(const std::string& str)
    throw(IfExc) -> CbitList;
  static auto _getTbits(const std::string& str, int first)
    throw(IfExc) -> TbitList;
  static auto _getGate(const std::string& line, const Counts& counts)
    throw(IfExc) -> GatePtr;

 public:
  static auto open(const std::string& filename) -> Circuit;
  static auto open(const char* const filename) -> Circuit;
};

inline auto Esop::_isCommentLine(const std::string& line) -> bool {
  return line.front() == '#';
}

inline auto Esop::_isEndLine(const std::string& line) -> bool {
  return line == ".e";
}

inline auto Esop::open(const char* const filename) -> Circuit {
  return Esop::open(std::string(filename));
}
}
}
