/**
 * @file parser_impl.hpp
 * @brief implementation header of Json::Parser class
 */

#pragma once

#include "../../issue.hpp"
#include "../../../util/string.hpp"

namespace qc {
namespace io {
inline Json::Parser::Parser(std::string const& filename)
  : filename_(filename) {}

/*
inline auto Json::Parser::_error(std::string const& code)
  throw(IfExc) -> void {
  auto const& msg = _get_error_message(code);
  error::issue(msg, line_, filename_, lines_counter_);
  throw exc::IllegalFormatException("Cannot parse a json file.");
}

template <class... Args>
auto Json::Parser::_error(std::string const& code, Args&&... args)
  throw(IfExc) -> void {
  auto const& raw_msg = _get_error_message(code);
  auto const& msg = util::string::format(raw_msg, std::forward<Args>(args)...);
  error::issue(msg, line_, filename_, lines_counter_);
  throw exc::IllegalFormatException("Cannot parse a json file.");
}

inline auto Json::Parser::_warn(std::string const& code) -> void {
  auto const& msg = _get_warn_message(code);
  warn::issue(msg, line_, filename_, lines_counter_);
}

template <class... Args>
auto Json::Parser::_warn(std::string const& code, Args&&... args) -> void {
  auto const& raw_msg = _get_warn_message(code);
  auto const& msg = util::string::format(raw_msg, std::forward<Args>(args)...);
  warn::issue(msg, line_, filename_, lines_counter_);
}
*/
}
}
