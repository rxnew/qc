#pragma once

#include "../gate_kernel.hpp"
#include "../gates_wrapper/gates_wrapper_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class GroupKernel : public GateKernel, public GatesWrapperKernel {
 public:
  static constexpr char const* const TYPE_NAME = "Group";
  static constexpr util::string::Aliases<6> const ALIASES = {
    "group",
    "module",
    "macrogate",
    "gatearray",
    "step",
    "pqgate"
  };

  template <class... Args>
  GroupKernel(Args&&... args);
  GroupKernel(GroupKernel const& other);
  GroupKernel(GroupKernel&& other) noexcept;

  ~GroupKernel() noexcept = default;

  auto operator=(GroupKernel const& other) -> GroupKernel&;
  auto operator=(GroupKernel&& other) noexcept -> GroupKernel&;
  auto operator==(GroupKernel const& other) const -> bool;
  auto operator!=(GroupKernel const& other) const -> bool;
  virtual auto operator==(GateKernel const& other) const -> bool final;
  virtual auto operator!=(GateKernel const& other) const -> bool final;

  virtual auto clone() const -> std::unique_ptr<GateKernel> final;
  virtual auto get_type_name() const -> std::string final;
  virtual auto is_group() const -> bool final;
  virtual auto get_cbits() -> CBits& final;
  virtual auto get_cbits() const -> CBits const& final;
  virtual auto get_tbits() -> TBits& final;
  virtual auto get_tbits() const -> TBits const& final;
  virtual auto get_gates() -> Gates& final;
  virtual auto get_gates() const -> Gates const& final;
  virtual auto print(std::ostream& os = std::cout) const -> void final;

 private:
  auto _get_cbits() const -> CBits&;
  auto _get_tbits() const -> TBits&;
};
}

#include "group_kernel/group_kernel_impl.hpp"
