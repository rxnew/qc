/**
 * @file parser.hpp
 * @brief header of qc::io::Blif::Parser class
 */

#pragma once

#include "../blif.hpp"

namespace qc {
namespace io {
class Blif::Parser {
 private:
  using Tokens = std::vector<std::string>;

  std::string filename_;

  mutable std::ifstream ifs_;
  mutable std::string model_name_;
  mutable std::unordered_set<std::string> input_wire_names_;
  mutable std::unordered_set<std::string> output_wire_names_;
  mutable std::string line_;
  mutable int lines_counter_;
  mutable std::unordered_map<std::string, Bitno> bit_map_;
  mutable int bit_counter_;
  mutable std::unordered_map<Bitno, GatePtr> middle_gate_map_;
  mutable GateList output_gates_;

  auto _init() -> void;
  auto _setTokens(Tokens& tokens) -> void;
    auto _parseLine()
    throw(IfExc) -> bool;
  auto _parseModelName(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseInputs(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseOutputs(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseClocks(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseGate(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseMlatch(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseLatch(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseNames(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseSubckt(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _parseGateParams(const std::string& token)
    throw(IfExc) ->  std::pair<std::string, std::string>;
  auto _createGateNand2(const Tokens& tokens)
    throw(IfExc) -> void;
  auto _createCircuit() -> Circuit;
  auto _placeGates(Circuit& circuit) -> void;
  auto _isAncilla(const std::string& wire_name) -> bool;
  auto _addBit(const std::string& wire_name) -> bool;
  auto _error(const std::string& code)
    throw(IfExc) -> void;
  template <class... Args>
  auto _error(const std::string& code, Args&&... args)
    throw(IfExc) -> void;
  auto _warn(const std::string& code) -> void;
  template <class... Args>
  auto _warn(const std::string& code, Args&&... args) -> void;

 public:
  Parser(const std::string& filename);
  ~Parser() = default;

  auto parse()
    throw(IfExc, std::ios_base::failure) -> Circuit;
};
}
}

#include "parser/parser_impl.hpp"
