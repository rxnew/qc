#include "../blif.hpp"

#include "../../algorithm/oracle.hpp"

namespace qc {
namespace io {
const std::string Blif::extension = ".blif";

auto Blif::_printGeneral(const Gate& gate, std::ostream& os,
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

auto Blif::_printGeneral(const Circuit& circuit, std::ostream& os) -> void {
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
    Blif::_printGeneral(*gate, os, wire, max_bit_t);
  }

  for(const auto& bit : bits) {
    os << ".names" << " x" << wire[bit] << " y" << bit << std::endl;
    os << "1 1" << std::endl;
  }
  os << ".end" << std::endl;
}

auto Blif::_printEsop(const Gate& gate, std::ostream& os) -> void {
  assert(gate.isControlled());
  for(const auto& tbit : gate.getTbitList()) {
    os << ".names";
    for(const auto& cbit : gate.getCbitList()) {
      os << " x" << cbit.bitno_;
    }
    os << " y" << tbit.bitno_ << std::endl;
    for(const auto& cbit : gate.getCbitList()) {
      os << (cbit.polarity_ ? '1' : '0');
    }
    os << " 1" << std::endl;
  }
}

auto Blif::_printEsop(const Circuit& circuit, std::ostream& os) -> void {
  using util::container::ordered;

  auto model_name = "circuit";
  os << ".model " << model_name << std::endl;

  auto inputs = ordered(qc::collectCbits(circuit));
  auto outputs = ordered(qc::collectTbits(circuit));

  os << ".inputs";
  for(const auto& bit : inputs) os << " x" << bit;
  os << std::endl;

  os << ".outputs";
  for(const auto& bit : outputs) os << " y" << bit;
  os << std::endl;

  for(const auto& gate : circuit.getGateList()) {
    Blif::_printEsop(*gate, os);
  }
  os << ".end" << std::endl;
}

auto Blif::output(const Circuit& circuit, const std::string& filename)
  throw(std::ios_base::failure) -> void {
  std::ofstream ofs(util::string::addExtension(filename, Blif::extension));
  if(ofs.fail()) throw std::ios_base::failure("Cannot open file.");
  Blif::print(circuit, ofs);
}

auto Blif::print(const Circuit& circuit, std::ostream& os) -> void {
  assert(qc::isMctCircuit(circuit));
  if(qc::isEsopCircuit(circuit)) Blif::_printEsop(circuit, os);
  else                           Blif::_printGeneral(circuit, os);
}
}
}
