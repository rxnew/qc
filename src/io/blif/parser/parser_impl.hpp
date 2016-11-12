/**
 * @file parser_impl.hpp
 * @brief implementation header of Blif::Parser class
 */

#pragma once

#include "../../warn.hpp"
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

inline auto Blif::Parser::_warn(const std::string& code) -> void {
  this->_warnMessage(Blif::_warn_msgs.at(code));
}

template <class... Args>
auto Blif::Parser::_warn(const std::string& code, Args&&... args) -> void {
  auto raw_msg = Blif::_warn_msgs.at(code);
  auto msg = util::string::format(raw_msg, std::forward<Args>(args)...);
  this->_warnMessage(msg);
}

inline auto Blif::Parser::_warnMessage(const std::string& raw_msg) -> void {
  auto msg = raw_msg + "\n  " + this->line_;
  warn::issue(msg, this->filename_, this->lines_counter_);
}
}
}
