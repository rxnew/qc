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
  static Messages const _err_msgs;

  Qo() = delete;

  static auto _create_circuit(std::ifstream& ifs)
    throw(IfExc) -> Circuit;
  static auto _create_group(std::ifstream& ifs)
    throw(IfExc) -> Gate;
  static auto _create_gate(std::string const& line)
    throw(IfExc) -> Gate;
  static auto _divide_data(std::string const& line)
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
