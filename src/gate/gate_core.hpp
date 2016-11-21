#pragma once

#include <memory>

#include "../forward_declarations.hpp"
#include "../bit/hash.hpp"

namespace qc {
class GateCore {
 public:
  virtual ~GateCore() noexcept = default;

 protected:
  GateCore() = default;
  explicit GateCore(TBit const& tbit);
  GateCore(CBit const& cbit, TBit const& tbit);
  GateCore(CBit const& cbit, TBits const& tbits);
  GateCore(CBit const& cbit, TBits&& tbits);
  GateCore(CBits const& cbits, TBit const& tbit);
  GateCore(CBits&& cbits, TBit const& tbit);
  GateCore(CBits const& cbits, TBits const& tbits);
  GateCore(CBits&& cbits, TBits&& tbits);
  //template <class... Args>
  //explict GateCore(Args&&... args);
  GateCore(GateCore const&) = default;
  GateCore(GateCore&&) noexcept = default;

  auto operator=(GateCore const&) -> GateCore& = default;
  auto operator=(GateCore&&) noexcept -> GateCore& = default;
  auto operator==(GateCore const& other) const -> bool;
  auto operator!=(GateCore const& other) const -> bool;

  virtual auto clone() const -> std::unique_ptr<GateCore> = 0;
  virtual auto get_type_name() const -> char const* const& = 0;
  virtual auto get_cbits() -> CBits&;
  virtual auto get_cbits() const -> CBits const&;
  virtual auto get_tbits() -> TBits&;
  virtual auto get_tbits() const -> TBits const&;
  virtual auto print(std::ostream& os = std::cout) const -> void;
  // for GateGroup
  virtual auto get_gates() -> Gates&;
  virtual auto get_gates() const -> Gates const&;

  CBits cbits_;
  TBits tbits_;

  friend class Gate;
  template <class GateCoreT>
  friend class GateType;
};
}

#include "gate_core/gate_core_impl.hpp"
