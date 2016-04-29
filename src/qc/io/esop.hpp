/**
 * @file esop.hpp
 * @brief header of qc::io::Esop class
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
  using Messages = std::array<std::string, 7>;
  using Counts = std::map<std::string, size_t>;

  static Messages _err_msgs;

  Esop() = delete;

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
  static std::string extension;

  static auto input(Circuit& circuit, const std::string& filename)
    throw(IfExc, std::ios_base::failure) -> void;
  static auto open(const std::string& filename)
    throw(IfExc, std::ios_base::failure) -> Circuit;
};
}
}

#include "esop_impl.hpp"
