/**
 * @file json.hpp
 * @brief header of qc::io::Json class
 */

#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "../forward_declarations.hpp"
#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
class Json {
 private:
  using IfExc = exc::IllegalFormatException;

 public:
  static constexpr char const* const extension = ".json";
  static constexpr char const* const format_type = "qc";

  static auto input(Circuit& circuit, std::string const& filename)
    throw(IfExc, std::ios_base::failure) -> void;
  static auto output(Circuit const& circuit, std::string const& filename)
    throw(std::ios_base::failure) -> void;
  static auto open(std::string const& filename)
    throw(IfExc, std::ios_base::failure) -> Circuit;
  static auto print(Circuit const& circuit,
                    std::ostream& os = std::cout) -> void;

 private:
  class Parser;
  class Dumper;

  using BitMap = std::unordered_map<BitNo, BitNo>;
  using Messages = std::unordered_map<std::string, std::string>;

  static Messages const _err_msgs;
  static Messages const _warn_msgs;

  Json() = delete;

  static auto _get_error_message(std::string const& code) -> std::string const&;
  static auto _get_warn_message(std::string const& code) -> std::string const&;
};
}
}

#include "json/json_impl.hpp"
