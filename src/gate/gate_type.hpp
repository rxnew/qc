#pragma once

#include "../gate.hpp"

namespace qc {
template <class GateKernelT>
class GateType : public Gate {
 public:
  static constexpr auto const& TYPE_NAME = GateKernelT::TYPE_NAME;
  static constexpr auto const& ALIASES = GateKernelT::ALIASES;

  template <class... Args>
  GateType(Args&&... args);
  GateType(GateType const& other);
  GateType(GateType&&) noexcept = default;

  ~GateType() noexcept = default;

  auto operator=(GateType const& gate) -> GateType&;
  auto operator=(GateType&& gate) noexcept -> GateType& = default;
};
}

#include "gate_type/gate_type_impl.hpp"
