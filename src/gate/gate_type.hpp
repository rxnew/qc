#pragma once

#include "../gate.hpp"

namespace qc {
template <class GateCoreT>
class GateType : public Gate {
 public:
  static constexpr char const* const TYPE_NAME = GateCoreT::TYPE_NAME;
  static constexpr auto const ALIASES = GateCoreT::ALIASES;

  template <class... Args>
  GateType(Args&&... args);
  GateType(GateType const& other);
  GateType(GateType&&) noexcept = default;
  template <class GateT>
  GateType(GateType<GateT> const& gate);
  template <class GateT>
  GateType(GateType<GateT>&& gate);

  ~GateType() noexcept = default;

  template <class GateT>
  auto operator=(GateType<GateT> const& gate) -> GateType&;
  template <class GateT>
  auto operator=(GateType<GateT>&& gate) -> GateType&;
};
}

#include "gate_type/gate_type_impl.hpp"
