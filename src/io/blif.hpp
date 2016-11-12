/**
 * @file blif.hpp
 * @brief header of qc::io::Blif class
 */

#pragma once

#include <fstream>

#include "../circuit.hpp"
#include "exc/illegal_format_exception.hpp"

namespace qc {
namespace io {
class Blif {
 private:
  class Parser;

  using IfExc = exc::IllegalFormatException;
  using BitMap = std::unordered_map<Bitno, Bitno>;
  using Messages = std::unordered_map<std::string, std::string>;

  static const Messages _err_msgs;
  static const Messages _warn_msgs;

  Blif() = delete;

  static auto _print(const Gate& gate, std::ostream& os,
                     BitMap& wire, Bitno& max_bit_t) -> void;
  static auto _print(const Circuit& circuit, std::ostream& os) -> void;

 public:
  static const std::string extension;

  static auto input(Circuit& circuit, const std::string& filename)
    throw(IfExc, std::ios_base::failure) -> void;
  static auto output(const Circuit& circuit, const std::string& filename)
    throw(std::ios_base::failure) -> void;
  static auto open(const std::string& filename)
    throw(IfExc, std::ios_base::failure) -> Circuit;
  static auto print(const Circuit& circuit,
                    std::ostream& os = std::cout) -> void;
};
}
}

#include "blif/blif_impl.hpp"
