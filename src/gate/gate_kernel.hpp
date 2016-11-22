#pragma once

#include <memory>

#include "../forward_declarations.hpp"
#include "../bit/hash.hpp"

namespace qc {
class GateKernel {
 public:
  GateKernel() = default;
  explicit GateKernel(TBit const& tbit);
  GateKernel(CBit const& cbit, TBit const& tbit);
  GateKernel(CBit const& cbit, TBits const& tbits);
  GateKernel(CBit const& cbit, TBits&& tbits);
  GateKernel(CBits const& cbits, TBit const& tbit);
  GateKernel(CBits&& cbits, TBit const& tbit);
  GateKernel(CBits const& cbits, TBits const& tbits);
  GateKernel(CBits&& cbits, TBits&& tbits);
  //template <class... Args>
  //explict GateKernel(Args&&... args);
  GateKernel(GateKernel const&) = default;
  GateKernel(GateKernel&&) noexcept = default;

  virtual ~GateKernel() noexcept = default;

  auto operator=(GateKernel const&) -> GateKernel& = default;
  auto operator=(GateKernel&&) noexcept -> GateKernel& = default;
  auto operator==(GateKernel const& other) const -> bool;
  auto operator!=(GateKernel const& other) const -> bool;

  virtual auto clone() const -> std::unique_ptr<GateKernel> = 0;
  virtual auto get_type_name() const -> char const* const& = 0;
  virtual auto is_group() const -> bool;
  virtual auto get_cbits() -> CBits&;
  virtual auto get_cbits() const -> CBits const&;
  virtual auto get_tbits() -> TBits&;
  virtual auto get_tbits() const -> TBits const&;
  virtual auto print(std::ostream& os = std::cout) const -> void;
  // for GateGroup
  virtual auto get_gates() -> Gates&;
  virtual auto get_gates() const -> Gates const&;

 protected:
  CBits cbits_;
  TBits tbits_;
};
}

#include "gate_kernel/gate_kernel_impl.hpp"
