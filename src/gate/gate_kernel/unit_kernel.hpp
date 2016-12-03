#pragma once

#include <memory>

#include "../gate_kernel.hpp"
#include "../../bit/bits_wrapper/bits_wrapper_kernel.hpp"

namespace qc {
class UnitKernel : public GateKernel, public BitsWrapperKernel {
 public:
  UnitKernel(std::initializer_list<CBit> cbits,
             std::initializer_list<TBit> tbits);
  UnitKernel(bool bedaggered,
             std::initializer_list<CBit> cbits,
             std::initializer_list<TBit> tbits);
  template <class... Args>
  UnitKernel(Args&&... args);
  template <class... Args>
  UnitKernel(bool bedaggered, Args&&... args);
  UnitKernel(UnitKernel const& other);
  UnitKernel(UnitKernel&& other) noexcept;

  virtual ~UnitKernel() noexcept = default;

  auto operator=(UnitKernel const& other) -> UnitKernel&;
  auto operator=(UnitKernel&& other) noexcept -> UnitKernel&;
  auto operator==(UnitKernel const& other) const -> bool;
  auto operator!=(UnitKernel const& other) const -> bool;
  virtual auto operator==(GateKernel const& other) const -> bool;
  virtual auto operator!=(GateKernel const& other) const -> bool;

  virtual auto is_group() const -> bool final;
  virtual auto bedaggered() const -> bool;
  virtual auto invert() -> void;
  virtual auto get_cbits() -> CBits& final;
  virtual auto get_cbits() const -> CBits const& final;
  virtual auto get_tbits() -> TBits& final;
  virtual auto get_tbits() const -> TBits const& final;
  virtual auto get_gates() -> Gates& final;
  virtual auto get_gates() const -> Gates const& final;
  virtual auto print(std::ostream& os = std::cout) const -> void final;

 protected:
  bool bedaggered_;
};
}

#include "unit_kernel/unit_kernel_impl.hpp"
