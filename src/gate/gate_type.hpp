#pragma once

#include "../gate.hpp"

namespace qc {
template <class GateCoreT>
class GateType : public Gate {
 public:
  static constexpr auto const& TYPE_NAME = GateCoreT::TYPE_NAME;
  static constexpr auto const& ALIASES = GateCoreT::ALIASES;

  template <class... Args>
  GateType(Args&&... args);
  GateType(GateType const& other);
  GateType(GateType&&) noexcept = default;
  template <class GateCoreU>
  GateType(GateType<GateCoreU> const& gate);
  template <class GateCoreU>
  GateType(GateType<GateCoreU>&& gate);

  ~GateType() noexcept = default;

  template <class GateCoreU>
  auto operator=(GateType<GateCoreU> const& gate) -> GateType&;
  template <class GateCoreU>
  auto operator=(GateType<GateCoreU>&& gate) -> GateType&;
};
}

#include "gate_type/gate_type_impl.hpp"
