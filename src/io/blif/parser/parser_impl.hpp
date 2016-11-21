/**
 * @file parser_impl.hpp
 * @brief implementation header of Blif::Parser class
 */

#pragma once

#include "../../issue.hpp"
#include "../../../util/string.hpp"

namespace qc {
namespace io {
inline Blif::Parser::Parser(std::string const& filename)
  : filename_(filename) {}

inline auto Blif::Parser::_is_ancilla(std::string const& wire_name) -> bool {
  return
    !(input_wire_names_.count(wire_name) ||
      output_wire_names_.count(wire_name));
}

inline auto Blif::Parser::_add_bit(std::string const& wire_name) -> bool {
  if(bit_map_.count(wire_name)) return false;
  bit_map_[wire_name] = static_cast<BitNo>(bit_counter_++);
  return true;
}

inline auto Blif::Parser::_error(std::string const& code)
  throw(IfExc) -> void {
  auto const& msg = _get_error_message(code);
  error::issue(msg, line_, filename_, lines_counter_);
  throw exc::IllegalFormatException("Cannot parse a blif file.");
}

template <class... Args>
auto Blif::Parser::_error(std::string const& code, Args&&... args)
  throw(IfExc) -> void {
  auto const& raw_msg = _get_error_message(code);
  auto const& msg = util::string::format(raw_msg, std::forward<Args>(args)...);
  error::issue(msg, line_, filename_, lines_counter_);
  throw exc::IllegalFormatException("Cannot parse a blif file.");
}

inline auto Blif::Parser::_warn(std::string const& code) -> void {
  auto const& msg = _get_warn_message(code);
  warn::issue(msg, line_, filename_, lines_counter_);
}

template <class... Args>
auto Blif::Parser::_warn(std::string const& code, Args&&... args) -> void {
  auto const& raw_msg = _get_warn_message(code);
  auto const& msg = util::string::format(raw_msg, std::forward<Args>(args)...);
  warn::issue(msg, line_, filename_, lines_counter_);
}
}
}
