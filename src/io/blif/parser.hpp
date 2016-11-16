/**
 * @file parser.hpp
 * @brief header of qc::io::Blif::Parser class
 */

#pragma once

#include "../blif.hpp"

#include <vector>

#include "../../gate.hpp"

namespace qc {
namespace io {
class Blif::Parser {
 public:
  Parser(std::string const& filename);
  ~Parser() = default;

  auto parse()
    throw(IfExc, std::ios_base::failure) -> Circuit;

 private:
  using Tokens = std::vector<std::string>;

  auto _init() -> void;
  auto _set_tokens(Tokens& tokens) -> void;
  auto _parse_line()
    throw(IfExc) -> bool;
  auto _parse_model_name(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_inputs(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_outputs(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_clocks(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_gate(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_mlatch(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_latch(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_names(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_subckt(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _parse_gate_params(std::string const& token)
    throw(IfExc) ->  std::pair<std::string, std::string>;
  auto _create_gate_nand2(Tokens const& tokens)
    throw(IfExc) -> void;
  auto _create_circuit() -> Circuit;
  auto _place_gates(Circuit& circuit) -> void;
  auto _is_ancilla(std::string const& wire_name) -> bool;
  auto _add_bit(std::string const& wire_name) -> bool;
  auto _error(std::string const& code)
    throw(IfExc) -> void;
  template <class... Args>
  auto _error(std::string const& code, Args&&... args)
    throw(IfExc) -> void;
  auto _warn(std::string const& code) -> void;
  template <class... Args>
  auto _warn(std::string const& code, Args&&... args) -> void;

  std::string filename_;

  mutable std::ifstream ifs_;
  mutable std::string model_name_;
  mutable std::unordered_set<std::string> input_wire_names_;
  mutable std::unordered_set<std::string> output_wire_names_;
  mutable std::string line_;
  mutable int lines_counter_;
  mutable std::unordered_map<std::string, BitNo> bit_map_;
  mutable int bit_counter_;
  mutable std::unordered_map<BitNo, Gate> middle_gate_map_;
  mutable Gates output_gates_;
};
}
}

#include "parser/parser_impl.hpp"
