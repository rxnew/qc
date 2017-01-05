#pragma once

#include <cassert>

#include "../../hash.hpp"

namespace qc {
inline auto BitsWrapperShell::set_cbits(CBits const& cbits) -> void {
  _get_cbits() = cbits;
}

inline auto BitsWrapperShell::set_cbits(CBits&& cbits) -> void {
  _get_cbits() = std::move(cbits);
}

inline auto BitsWrapperShell::set_tbits(TBits const& tbits) -> void {
  _get_tbits() = tbits;
}

inline auto BitsWrapperShell::set_tbits(TBits&& tbits) -> void {
  _get_tbits() = std::move(tbits);
}

inline auto BitsWrapperShell::add_cbit(CBit const& cbit) -> void {
  _get_cbits().insert(cbit);
}

inline auto BitsWrapperShell::add_cbit(BitNo bit_no, bool polarity) -> void {
  _get_cbits().emplace(bit_no, polarity);
}

template <template <class...> class Container>
auto BitsWrapperShell::add_cbit(Container<BitNo> const& bit_nos, bool polarity)
  -> void {
  for(auto const& bit : bit_nos) {
    add_cbit(bit, polarity);
  }
}

template <template <class...> class Container>
auto BitsWrapperShell::add_cbit(Container<CBit> const& cbits) -> void {
  for(auto const& cbit : cbits) {
    add_cbit(cbit);
  }
}

inline auto BitsWrapperShell::add_tbit(TBit const& tbit) -> void {
  _get_tbits().insert(tbit);
}

inline auto BitsWrapperShell::add_tbit(BitNo bit_no) -> void {
  _get_tbits().emplace(bit_no);
}

template <template <class...> class Container>
auto BitsWrapperShell::add_tbit(Container<BitNo> const& bit_nos)
  -> void {
  for(auto const& bit : bit_nos) {
    add_tbit(bit);
  }
}

template <template <class...> class Container>
auto BitsWrapperShell::add_tbit(Container<TBit> const& tbits) -> void {
  for(auto const& tbit : tbits) {
    add_tbit(tbit);
  }
}

inline auto BitsWrapperShell::has_bit(BitNo bit_no) const -> bool {
  return has_tbit(bit_no) || has_cbit(bit_no);
}

inline auto BitsWrapperShell::has_cbit(CBit const& cbit) const -> bool {
  return get_cbits().count(cbit);
}

inline auto BitsWrapperShell::has_cbit(BitNo bit_no) const -> bool {
  return has_cbit(CBit(bit_no, true)) || has_cbit(CBit(bit_no, false));
}

inline auto BitsWrapperShell::has_tbit(TBit const& tbit) const -> bool {
  return get_tbits().count(tbit);
}

inline auto BitsWrapperShell::has_tbit(BitNo bit_no) const -> bool {
  return has_tbit(TBit(bit_no));
}

inline auto BitsWrapperShell::erase_bit(Bit const& bit) -> size_t {
  return erase_bit(bit.get_no());
}

inline auto BitsWrapperShell::erase_bit(BitNo bit_no) -> size_t {
  return
    _get_cbits().erase(get_cbit(bit_no)) || _get_tbits().erase(TBit(bit_no));
}

inline auto BitsWrapperShell::get_cbit_polarity(BitNo bit_no) const -> bool {
  assert(has_cbit(bit_no));
  return get_cbits().count(CBit(bit_no, true));
}

inline auto BitsWrapperShell::is_controlled() const -> bool {
  return !get_cbits().empty();
}

inline auto BitsWrapperShell::is_single_controlled() const -> bool {
  return get_cbits().size() == 1u;
}

inline auto BitsWrapperShell::is_multi_controlled() const -> bool {
  return get_cbits().size() > 1u;
}

inline auto BitsWrapperShell::is_single_target() const -> bool {
  return get_tbits().size() == 1u;
}

inline auto BitsWrapperShell::is_multi_target() const -> bool {
  return get_tbits().size() > 1u;
}

inline auto BitsWrapperShell::is_single_qubit_rotation() const -> bool {
  return !is_controlled() && is_single_target();
}
}
