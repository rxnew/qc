/**
 * @file parser_impl.hpp
 * @brief implementation header of Blif::Parser class
 */

#pragma once

#include "../../issue.hpp"
#include "../../../util/string.hpp"

namespace qc {
namespace io {
inline Blif::Parser::Parser(const std::string& filename)
  : filename_(filename) {}

inline auto Blif::Parser::_isAncilla(const std::string& wire_name) -> bool {
  return
    !(this->input_wire_names_.count(wire_name) ||
      this->output_wire_names_.count(wire_name));
}

inline auto Blif::Parser::_addBit(const std::string& wire_name) -> bool {
  if(this->bit_map_.count(wire_name)) return false;
  this->bit_map_[wire_name] = static_cast<Bitno>(this->bit_counter_++);
  return true;
}

inline auto Blif::Parser::_error(const std::string& code)
  throw(IfExc) -> void {
  const auto& msg = Blif::_getErrorMessage(code);
  error::issue(msg, this->line_, this->filename_, this->lines_counter_);
}

template <class... Args>
auto Blif::Parser::_error(const std::string& code, Args&&... args)
  throw(IfExc) -> void {
  const auto& raw_msg = Blif::_getErrorMessage(code);
  const auto msg = util::string::format(raw_msg, std::forward<Args>(args)...);
  error::issue(msg, this->line_, this->filename_, this->lines_counter_);
}

inline auto Blif::Parser::_warn(const std::string& code) -> void {
  const auto& msg = Blif::_getWarnMessage(code);
  warn::issue(msg, this->line_, this->filename_, this->lines_counter_);
}

template <class... Args>
auto Blif::Parser::_warn(const std::string& code, Args&&... args) -> void {
  const auto& raw_msg = Blif::_getWarnMessage(code);
  const auto msg = util::string::format(raw_msg, std::forward<Args>(args)...);
  warn::issue(msg, this->line_, this->filename_, this->lines_counter_);
}
}
}
