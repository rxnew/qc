/**
 * @file esop.hpp
 * @brief header of qc::io::Esop class
 */

#pragma once

#include <fstream>
#include <iostream>
#include <set>

#include "../forward_declarations.hpp"
#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
class Esop {
 private:
  using IfExc = exc::IllegalFormatException;

 public:
  static constexpr char const* const extension = ".esop";

  static auto input(Circuit& circuit, std::string const& filename)
    throw(IfExc, std::ios_base::failure) -> void;
  static auto output(Circuit const& circuit, std::string const& filename)
    throw(std::ios_base::failure) -> void;
  static auto open(std::string const& filename)
    throw(IfExc, std::ios_base::failure) -> Circuit;
  static auto print(Circuit const& circuit,
                    std::ostream& os = std::cout) -> void;

 private:
  using Counts = std::unordered_map<std::string, size_t>;
  using Messages = std::array<char const* const, 7>;

  static Messages const _err_msgs;

  Esop() = delete;

  static auto _is_comment_line(std::string const& line) -> bool;
  static auto _is_end_line(std::string const& line) -> bool;
  static auto _set_count(Counts& counts, std::string const& line)
    throw(IfExc) -> void;
  static auto _get_counts(std::ifstream& ifs)
    throw(IfExc) -> Counts;
  static auto _get_cbits(std::string const& str)
    throw(IfExc) -> CBits;
  static auto _get_tbits(std::string const& str, int first)
    throw(IfExc) -> TBits;
  static auto _get_gate(std::string const& line, Counts const& counts)
    throw(IfExc) -> Gate;
  static auto _print(Gate const& gate, std::ostream& os,
                     std::set<BitNo> const& inputs,
                     std::set<BitNo> const& outputs) -> void;
  static auto _print(Circuit const& circuit, std::ostream& os) -> void;
};
}
}

#include "esop/esop_impl.hpp"
