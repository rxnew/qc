/**
 * @file gate.hpp
 * @brief header of Gate class
 */

#pragma once

#include <memory>

#include "forward_declarations.hpp"
#include "bit/hash.hpp"
#include "gate/gates_wrapper/gates_wrapper_shell.hpp"

namespace qc {
class GateKernel;

class Gate : public GatesWrapperShell {
 public:
  Gate(Gate const& other);
  Gate(Gate&& other) noexcept = default;

  ~Gate() noexcept = default;

  template <class Type, class... Args>
  static auto make(Args&&... args) -> Gate;
  static auto make_dummy(bool assert_flag = true) -> Gate;

  auto operator=(Gate const&) -> Gate&;
  auto operator=(Gate&&) noexcept -> Gate& = default;
  auto operator==(Gate const& other) const -> bool;
  auto operator!=(Gate const& other) const -> bool;

  auto get_type_name() const -> char const* const&;
  auto get_cbits() const -> CBits const&;
  auto get_tbits() const -> TBits const&;
  auto set_cbits(CBits const& cbits) -> void;
  auto set_cbits(CBits&& cbits) -> void;
  auto set_tbits(TBits const& tbits) -> void;
  auto set_tbits(TBits&& tbits) -> void;
  auto add_cbit(CBit const& cbit) -> void;
  auto add_cbit(BitNo bit_no, bool polarity = true) -> void;
  auto add_tbit(TBit const& tbit) -> void;
  auto add_tbit(BitNo bit_no) -> void;
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
  auto print(std::ostream& os = std::cout) const -> void;
  // for Group
  auto is_group() const -> bool;
  auto get_gates() const -> Gates const&;

 protected:
  explicit Gate(std::unique_ptr<GateKernel>&& kernel);
  explicit Gate(GateKernel*&& kernel);

  auto get_gates() -> Gates&;

  std::unique_ptr<GateKernel> kernel_;
};
}

#include "gate/gate_impl.hpp"
