/**
 * @file dumper.hpp
 * @brief header of qc::io::Blif::Dumper class
 */

#pragma once

#include "../blif.hpp"

namespace qc {
namespace io {
class Blif::Dumper {
 private:
  const Circuit* const circuit_;
  std::ostream* const os_;

  auto _dumpGate(const Gate& gate, BitMap& wire, Bitno& max_bit_t) -> void;
  auto _dump() -> void;

 public:
  Dumper(const Circuit& circuit, std::ostream& os);
  ~Dumper() = default;

  auto dump() -> void;
};
}
}

#include "dumper/dumper_impl.hpp"
