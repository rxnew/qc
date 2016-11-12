#include "../dumper.hpp"

#include "../../../debug/issue.hpp"

namespace qc {
namespace io {
auto Blif::Dumper::_dumpGate(const Gate& gate, BitMap& wire,
                             Bitno& max_bit_t) -> void {
  for(const auto& tbit : gate.getTbitList()) {
    // just NOT gate
    if(!gate.isControlled()) {
      *this->os_ << ".names"
                 << " x" << wire[tbit.bitno_]
                 << " x";
      wire[tbit.bitno_] = ++max_bit_t;
      *this->os_ << max_bit_t << std::endl;
      *this->os_ << "0 1" << std::endl;
    }
    // AND and XOR is necessary
    else {
      // AND gates
      *this->os_ << ".names";
      for(const auto& cbit : gate.getCbitList()) {
        *this->os_ << " x" << cbit.bitno_;
      }
      *this->os_ << " x" << ++max_bit_t << std::endl;
      for(const auto& cbit : gate.getCbitList()) {
        *this->os_ << (cbit.polarity_ ? '1' : '0');
      }
      *this->os_ << " 1" << std::endl;

      // XOR gates
      *this->os_ << ".names"
                 << " x" << wire[tbit.bitno_]
                 << " x" << max_bit_t
                 << " x";
      wire[tbit.bitno_] = ++max_bit_t;
      *this->os_ << max_bit_t << std::endl;
      *this->os_ << "01 1" << std::endl;
      *this->os_ << "10 1" << std::endl;
    }
  }
}

auto Blif::Dumper::_dump() -> void {
  auto model_name = this->circuit_->getDescription();
  *this->os_ << ".model "
             << (model_name.empty() ? "circuit" : model_name) << std::endl;

  const auto bits = util::container::ordered(this->circuit_->collectUsedBits());
  const auto max_bit = *max_element(bits.cbegin(), bits.cend());
  auto max_bit_t = max_bit;

  BitMap wire(bits.size());
  for(const auto& bit : bits) wire[bit] = bit;

  *this->os_ << ".inputs";
  for(const auto& bit : bits) *this->os_ << " x" << bit;
  *this->os_ << std::endl;

  *this->os_ << ".outputs";
  for(const auto& bit : bits) *this->os_ << " y" << bit;
  *this->os_ << std::endl;

  for(const auto& gate : this->circuit_->getGateList()) {
    this->_dumpGate(*gate, wire, max_bit_t);
  }

  for(const auto& bit : bits) {
    *this->os_ << ".names" << " x" << wire[bit] << " y" << bit << std::endl;
    *this->os_ << "1 1" << std::endl;
  }
  *this->os_ << ".end" << std::endl;
}

auto Blif::Dumper::dump() -> void {
  if(!qc::isMctCircuit(*this->circuit_)) {
    debug::warn::issue(Blif::_getWarnMessage("W100"));
    return;
  }
  this->_dump();
}
}
}
