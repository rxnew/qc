/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "gate_private.hpp"
#include "../gate.hpp"

#include <set>

#include "../util/container.hpp"

namespace qc {
auto Gate::get_cbit(BitNo bit_no) const -> Cbit const& {
  auto cbit_pos = impl_->cbits_.find(Cbit(bit_no, true));
  if(cbit_pos != impl_->cbits_.cend()) return *cbit_pos;
  cbit_pos = impl_->cbits_.find(Cbit(bit_no, false));
  assert(cbit_pos != impl_->cbits_.cend());
  return *cbit_pos;
}

auto Gate::get_tbit(BitNo bit_no) const -> Tbit const& {
  const auto tbit_pos = impl_->tbits_.find(Tbit(bit_no));
  assert(tbit_pos != impl_->tbits_.cend());
  return *tbit_pos;
}

auto Gate::invert_cbit_polarity(BitNo bit_no) -> bool {
  auto polarity = get_cbit_polarity(bit_no);
  impl_->cbits_.erase(Cbit(bit_no, polarity));
  add_cbit(bit_no, polarity ^= true);
  return polarity;
}

auto Gate::collect_bits() const -> BitNos {
  auto bit_nos = BitNos();
  for(auto const& cbit : impl_->cbits_) {
    bit_nos.insert(cbit.get_no());
  }
  for(auto const& tbit : impl_->tbits_) {
    bit_nos.insert(tbit.get_no());
  }
  return bit_nos;
}

auto Gate::is_all_positive() const -> bool {
  for(auto const& cbit : impl_->cbits_) {
    if(!cbit.get_polarity()) return false;
  }
  return true;
}
}
