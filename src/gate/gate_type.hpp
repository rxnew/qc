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
  template <class GateKernelU>
  GateType(GateType<GateKernelU> const& gate);
  template <class GateKernelU>
  GateType(GateType<GateKernelU>&& gate);

  ~GateType() noexcept = default;

  template <class GateKernelU>
  auto operator=(GateType<GateKernelU> const& gate) -> GateType&;
  template <class GateKernelU>
  auto operator=(GateType<GateKernelU>&& gate) -> GateType&;
};
}

#include "gate_type/gate_type_impl.hpp"
