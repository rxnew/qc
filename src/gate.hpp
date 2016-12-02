/**
 * @file gate.hpp
 * @brief header of Gate class
 */

#pragma once

#include <memory>

#include "forward_declarations.hpp"
#include "bit/bits_wrapper/bits_wrapper_shell.hpp"
#include "gate/gates_wrapper/gates_wrapper_shell.hpp"
#include "gate/gate_kernel.hpp"

namespace qc {
enum class GateType;

class Gate : public BitsWrapperShell, public GatesWrapperShell {
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

  auto get_type() const -> GateType;
  auto get_type_name() const -> std::string;
  auto is_group() const -> bool;

  virtual auto get_cbits() const -> CBits const& final;
  virtual auto get_tbits() const -> TBits const& final;
  virtual auto get_gates() const -> Gates const& final;
  virtual auto print(std::ostream& os = std::cout) const -> void final;
  virtual auto collect_bits() const -> BitNos final;

 protected:
  explicit Gate(std::unique_ptr<GateKernel>&& kernel);
  explicit Gate(GateKernel*&& kernel);

  virtual auto _get_cbits() -> CBits& final;
  virtual auto _get_tbits() -> TBits& final;
  virtual auto _get_gates() -> Gates& final;

  std::unique_ptr<GateKernel> kernel_;
};
}

#include "gate/gate_impl.hpp"
