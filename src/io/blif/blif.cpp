#include "../blif.hpp"

namespace qc {
namespace io {
const std::string Blif::extension = ".blif";

auto Blif::_print(const Gate& gate, std::ostream& os,
                  BitMap& wire, Bitno& max_bit_t) -> void {
  for(const auto& tbit : gate.getTbitList()) {
    // just NOT gate
    if(!gate.isControlled()) {
      os << ".names" << " x" << wire[tbit.bitno_] << " x";
      wire[tbit.bitno_] = ++max_bit_t;
      os << max_bit_t << std::endl;
      os << "0 1" << std::endl;
    }
    // AND and XOR is necessary
    else {
      // AND gates
      os << ".names";
      for(const auto& cbit : gate.getCbitList()) {
        os << " x" << cbit.bitno_;
      }
      os << " x" << ++max_bit_t << std::endl;
      for(const auto& cbit : gate.getCbitList()) {
        os << (cbit.polarity_ ? '1' : '0');
      }
      os << " 1" << std::endl;

      // XOR gates
      os << ".names" << " x" << wire[tbit.bitno_] << " x" << max_bit_t << " x";
      wire[tbit.bitno_] = ++max_bit_t;
      os << max_bit_t << std::endl;
      os << "01 1" << std::endl;
      os << "10 1" << std::endl;
    }
  }
}

auto Blif::_print(const Circuit& circuit, std::ostream& os) -> void {
  auto model_name = "circuit";
  os << ".model " << model_name << std::endl;

  auto bits = util::container::ordered(circuit.collectUsedBits());
  auto max_bit = *max_element(bits.cbegin(), bits.cend());
  auto max_bit_t = max_bit;

  BitMap wire(bits.size());
  for(const auto& bit : bits) wire[bit] = bit;

  os << ".inputs";
  for(const auto& bit : bits) os << " x" << bit;
  os << std::endl;

  os << ".outputs";
  for(const auto& bit : bits) os << " y" << bit;
  os << std::endl;

  for(const auto& gate : circuit.getGateList()) {
    Blif::_print(*gate, os, wire, max_bit_t);
  }

  for(const auto& bit : bits) {
    os << ".names" << " x" << wire[bit] << " y" << bit << std::endl;
    os << "1 1" << std::endl;
  }
  os << ".end" << std::endl;
}

auto Blif::output(const Circuit& circuit, const std::string& filename)
  throw(std::ios_base::failure) -> void {
  std::ofstream ofs(util::string::addExtension(filename, Blif::extension));
  if(ofs.fail()) throw std::ios_base::failure("Cannot open file.");
  Blif::print(circuit, ofs);
}
}
}
