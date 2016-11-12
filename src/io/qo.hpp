/**
 * @file qo.hpp
 * @brief header of qc::io::Qo class
 */

#pragma once

#include <fstream>
#include <tuple>

#include "../circuit.hpp"
#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
class Qo {
 private:
  using IfExc = exc::IllegalFormatException;
  using Messages = std::array<std::string, 5>;
  using strings = std::vector<std::string>;
  using BitListTuple = std::tuple<CbitList, TbitList>;

  static Messages _err_msgs;

  Qo() = delete;

  static auto _divideIntoGroups(const std::string& line)
    throw(IfExc) -> strings;
  static auto _getGateString(const std::string& str)
    throw(IfExc) -> std::string;
  static auto _getBitStrings(const std::string& str)
    throw(IfExc) -> strings;
  static auto _getOptionStrings(const std::string& str)
    throw(IfExc) -> strings;
  static auto _getCbit(const std::string& bit_str)
    throw(IfExc) -> Cbit;
  static auto _getTbit(const std::string& bit_str)
    throw(IfExc) -> Tbit;
  static auto _getBits(const strings& bit_strs)
    throw(IfExc) -> BitListTuple;
  static auto _getGate(const std::string& gate_str, const BitListTuple& bits)
    -> GatePtr;

 public:
  static const std::string extension;

  static auto input(Circuit& circuit, const std::string& filename)
    throw(IfExc, std::ios_base::failure) -> void;
  static auto output(const Circuit& circuit, const std::string& filename)
    throw(std::ios_base::failure) -> void;
  static auto open(const std::string& filename)
    throw(IfExc, std::ios_base::failure) -> Circuit;
  static auto print(const Circuit& circuit,
                    std::ostream& os = std::cout) -> void;
};
}
}

#include "qo/qo_impl.hpp"
