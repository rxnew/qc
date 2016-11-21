#include "../dumper.hpp"

#include "../../../circuit.hpp"
#include "../../../debug/issue.hpp"
#include "../../../util/container.hpp"

namespace qc {
namespace io {
auto Blif::Dumper::dump() -> void {
  if(!is_mct_circuit(*circuit_)) {
    debug::warn::issue(_get_warn_message("W100"));
    return;
  }
  _dump();
}

auto Blif::Dumper::_dump_gate(Gate const& gate, BitMap& wire, BitNo& max_bit_t)
  -> void {
  for(auto const& tbit : gate.get_tbits()) {
    // just NOT gate
    if(!gate.is_controlled()) {
      *os_ << ".names"
           << " x" << wire[tbit.get_no()]
           << " x";
      wire[tbit.get_no()] = ++max_bit_t;
      *os_ << max_bit_t << std::endl;
      *os_ << "0 1" << std::endl;
    }
    // AND and XOR is necessary
    else {
      // AND gates
      *os_ << ".names";
      for(auto const& cbit : gate.get_cbits()) {
        *os_ << " x" << cbit.get_no();
      }
      *os_ << " x" << ++max_bit_t << std::endl;
      for(auto const& cbit : gate.get_cbits()) {
        *os_ << (cbit.get_polarity() ? '1' : '0');
      }
      *os_ << " 1" << std::endl;

      // XOR gates
      *os_ << ".names"
           << " x" << wire[tbit.get_no()]
           << " x" << max_bit_t
           << " x";
      wire[tbit.get_no()] = ++max_bit_t;
      *os_ << max_bit_t << std::endl;
      *os_ << "01 1" << std::endl;
      *os_ << "10 1" << std::endl;
    }
  }
}

auto Blif::Dumper::_dump() -> void {
  auto const& model_name = circuit_->get_description();
  *os_ << ".model "
       << (model_name.empty() ? "circuit" : model_name) << std::endl;

  auto const bits = util::container::ordered(circuit_->collect_bits());
  auto const max_bit = *max_element(bits.cbegin(), bits.cend());
  auto max_bit_t = max_bit;

  auto wire = BitMap(bits.size());
  for(auto const& bit : bits) wire[bit] = bit;

  *os_ << ".inputs";
  for(auto const& bit : bits) *os_ << " x" << bit;
  *os_ << std::endl;

  *os_ << ".outputs";
  for(auto const& bit : bits) *os_ << " y" << bit;
  *os_ << std::endl;

  for(auto const& gate : circuit_->get_gates()) {
    _dump_gate(gate, wire, max_bit_t);
  }

  for(auto const& bit : bits) {
    *os_ << ".names"
         << " x" << wire[bit]
         << " y" << bit << std::endl;
    *os_ << "1 1" << std::endl;
  }
  *os_ << ".end" << std::endl;
}
}
}
