/**
 * @file dumper.hpp
 * @brief header of qc::io::Blif::Dumper class
 */

#pragma once

#include "../blif.hpp"

namespace qc {
namespace io {
class Blif::Dumper {
 public:
  Dumper(Circuit const& circuit, std::ostream& os);
  ~Dumper() = default;

  auto dump() -> void;

 private:
  Circuit const* const circuit_;
  std::ostream* const os_;

  auto _dump_gate(Gate const& gate, BitMap& wire, BitNo& max_bit_t) -> void;
  auto _dump() -> void;
};
}
}

#include "dumper/dumper_impl.hpp"
