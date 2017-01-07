/**
 * @file parser.hpp
 * @brief header of qc::io::Json::Parser class
 */

#pragma once

#include "json11.hpp"

#include "../json.hpp"

namespace qc {
namespace io {
class Json::Parser {
 public:
  Parser(std::string const& filename);
  ~Parser() = default;

  auto parse()
    throw(IfExc, std::ios_base::failure) -> Circuit;

 private:
  auto _parse(json11::Json const& json)
    throw(IfExc) -> Circuit;
  auto _make_gate(json11::Json const& json)
    throw(IfExc) -> Gate;
  auto _get_type_name(json11::Json const& json)
    throw(IfExc) -> std::string const&;
  auto _get_cbits(json11::Json const& json)
    throw(IfExc) -> CBits;
  auto _get_tbits(json11::Json const& json)
    throw(IfExc) -> TBits;
  auto _check_format_type(json11::Json const& json)
    throw(IfExc) -> void;
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
};
}
}

#include "parser/parser_impl.hpp"
