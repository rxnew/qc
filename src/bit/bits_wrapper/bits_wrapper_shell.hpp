#pragma once

#include "../../forward_declarations.hpp"

namespace qc {
class BitsWrapperShell {
 public:
  BitsWrapperShell() = default;

  virtual ~BitsWrapperShell() noexcept = default;

  virtual auto get_cbits() const -> CBits const& = 0;
  virtual auto get_tbits() const -> TBits const& = 0;
  auto set_cbits(CBits const& cbits) -> void;
  auto set_cbits(CBits&& cbits) -> void;
  auto set_tbits(TBits const& tbits) -> void;
  auto set_tbits(TBits&& tbits) -> void;
  auto add_cbit(CBit const& cbit) -> void;
  auto add_cbit(BitNo bit_no, bool polarity = true) -> void;
  template <template <class...> class Container>
  auto add_cbit(Container<BitNo> const& bit_nos, bool polarity = true) -> void;
  template <template <class...> class Container>
  auto add_cbit(Container<CBit> const& cbits) -> void;
  auto add_tbit(TBit const& tbit) -> void;
  auto add_tbit(BitNo bit_no) -> void;
  template <template <class...> class Container>
  auto add_tbit(Container<BitNo> const& bit_nos) -> void;
  template <template <class...> class Container>
  auto add_tbit(Container<TBit> const& tbits) -> void;
  auto has_bit(BitNo bit_no) const -> bool;
  auto has_cbit(CBit const& cbit) const -> bool;
  auto has_cbit(BitNo bit_no) const -> bool;
  auto has_tbit(TBit const& tbit) const -> bool;
  auto has_tbit(BitNo bit_no) const -> bool;
  auto erase_bit(Bit const& bit) -> size_t;
  auto erase_bit(BitNo bit_no) -> size_t;
  auto get_cbit(BitNo bit_no) const -> CBit const&;
  auto get_tbit(BitNo bit_no) const -> TBit const&;
  auto get_cbit_polarity(BitNo bit_no) const -> bool;
  auto invert_cbit_polarity(BitNo bit_no) -> bool;
  auto collect_bits() const -> BitNos;
  auto is_controlled() const -> bool;
  auto is_single_controlled() const -> bool;
  auto is_multi_controlled() const -> bool;
  auto is_single_target() const -> bool;
  auto is_multi_target() const -> bool;
  auto is_single_qubit_rotation() const -> bool;
  auto is_all_positive() const -> bool;

 protected:
  virtual auto _get_cbits() -> CBits& = 0;
  virtual auto _get_tbits() -> TBits& = 0;
};
}

#include "bits_wrapper_shell/bits_wrapper_shell_impl.hpp"
