/**
 * @file blif.hpp
 * @brief header of qc::io::Blif class
 */

#pragma once

#include <fstream>
#include <vector>

#include "../circuit.hpp"

namespace qc {
namespace io {
class Blif {
 private:
  using BitMap = std::unordered_map<Bitno, Bitno>;

  Blif() = delete;

  static auto _printGeneral(const Gate& gate, std::ostream& os,
                            BitMap& wire, Bitno& max_bit_t) -> void;
  static auto _printGeneral(const Circuit& circuit, std::ostream& os) -> void;
  static auto _printEsop(const Gate& gate, std::ostream& os) -> void;
  static auto _printEsop(const Circuit& circuit, std::ostream& os) -> void;

 public:
  static const std::string extension;

  static auto output(const Circuit& circuit, const std::string& filename)
    throw(std::ios_base::failure) -> void;
  static auto print(const Circuit& circuit, std::ostream& os) -> void;
};
}
}

#include "blif/blif_impl.hpp"
