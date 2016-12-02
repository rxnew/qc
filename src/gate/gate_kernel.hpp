#pragma once

#include <memory>

#include "../forward_declarations.hpp"
#include "../bit/hash.hpp"

namespace qc {
class GateKernel {
 public:
  GateKernel() = default;

  virtual ~GateKernel() noexcept = default;

  virtual auto operator==(GateKernel const& other) const -> bool;
  virtual auto operator!=(GateKernel const& other) const -> bool;

  virtual auto clone() const -> std::unique_ptr<GateKernel> = 0;
  virtual auto get_type_name() const -> std::string = 0;
  virtual auto is_group() const -> bool = 0;
  virtual auto get_cbits() -> CBits& = 0;
  virtual auto get_cbits() const -> CBits const& = 0;
  virtual auto get_tbits() -> TBits& = 0;
  virtual auto get_tbits() const -> TBits const& = 0;
  virtual auto get_gates() -> Gates& = 0;
  virtual auto get_gates() const -> Gates const& = 0;
  virtual auto print(std::ostream& os = std::cout) const -> void = 0;
};
}

#include "gate_kernel/gate_kernel_impl.hpp"
