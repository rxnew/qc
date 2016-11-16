/**
 * @file qo.hpp
 * @brief header of qc::io::Qo class
 */

#pragma once

#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "../forward_declarations.hpp"
#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
class Qo {
 private:
  using IfExc = exc::IllegalFormatException;
  using Messages = std::array<char const* const, 5>;
  using strings = std::vector<std::string>;
  using BitsTuple = std::tuple<CBits, TBits>;

 public:
  static constexpr char const* const extension = ".qo";

  static auto input(Circuit& circuit, std::string const& filename)
    throw(IfExc, std::ios_base::failure) -> void;
  static auto output(Circuit const& circuit, std::string const& filename)
    throw(std::ios_base::failure) -> void;
  static auto open(std::string const& filename)
    throw(IfExc, std::ios_base::failure) -> Circuit;
  static auto print(Circuit const& circuit,
                    std::ostream& os = std::cout) -> void;

 private:
  static constexpr Messages const _err_msgs = {
    "Illegal format of gates. Too many or few parameters.",
    "Illegal format of gates. Gate name contains spaces.",
    "Illegal format of gates. Contorol and target bits is empty.",
    "Illegal format of gates. Bit is not numberic.",
    "Illegal format of gates. Unknown gate name."
  };

  Qo() = delete;

  static auto _divide_into_groups(std::string const& line)
    throw(IfExc) -> strings;
  static auto _get_gate_string(std::string const& str)
    throw(IfExc) -> std::string;
  static auto _get_bit_strings(std::string const& str)
    throw(IfExc) -> strings;
  static auto _get_option_strings(std::string const& str)
    throw(IfExc) -> strings;
  static auto _get_cbit(std::string const& bit_str)
    throw(IfExc) -> CBit;
  static auto _get_tbit(std::string const& bit_str)
    throw(IfExc) -> TBit;
  static auto _get_bits(strings const& bit_strs)
    throw(IfExc) -> BitsTuple;
  static auto _get_gate(std::string const& gate_str, BitsTuple const& bits)
    -> Gate;
};
}
}
