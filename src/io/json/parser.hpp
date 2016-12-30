/**
 * @file parser.hpp
 * @brief header of qc::io::Json::Parser class
 */

#pragma once

#include "../json.hpp"

#include <vector>

#include "../../circuit.hpp"

namespace qc {
namespace io {
class Json::Parser {
 public:
  Parser(std::string const& filename);
  ~Parser() = default;

  auto parse()
    throw(IfExc, std::ios_base::failure) -> Circuit;

 private:
  auto _error(std::string const& code)
    throw(IfExc) -> void;
  template <class... Args>
  auto _error(std::string const& code, Args&&... args)
    throw(IfExc) -> void;
  auto _warn(std::string const& code) -> void;
  template <class... Args>
  auto _warn(std::string const& code, Args&&... args) -> void;

  std::string filename_;

  mutable Circuit circuit_;
  mutable std::ifstream ifs_;
};
}
}

#include "parser/parser_impl.hpp"
