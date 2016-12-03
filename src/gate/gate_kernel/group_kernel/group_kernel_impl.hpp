#pragma once

namespace qc {
template <class... Args>
inline GroupKernel::GroupKernel(Args&&... args)
  : GatesWrapperKernel(std::forward<Args>(args)...) {}

inline GroupKernel::GroupKernel(GroupKernel const& other)
  : GatesWrapperKernel(other) {}

inline GroupKernel::GroupKernel(GroupKernel&& other) noexcept
  : GatesWrapperKernel(std::move(other)) {}

inline auto GroupKernel::operator=(GroupKernel const& other) -> GroupKernel& {
  GatesWrapperKernel::operator=(other);
  return *this;
}

inline auto GroupKernel::operator=(GroupKernel&& other) noexcept -> GroupKernel& {
  GatesWrapperKernel::operator=(std::move(other));
  return *this;
}

inline auto GroupKernel::operator==(GroupKernel const& other) const -> bool {
  return GateKernel::operator==(other) && GatesWrapperKernel::operator==(other);
}

inline auto GroupKernel::operator!=(GroupKernel const& other) const -> bool {
  return !(*this == other);
}

inline auto GroupKernel::operator==(GateKernel const& other) const -> bool {
  return GateKernel::operator==(other) && get_gates() == other.get_gates();
}

inline auto GroupKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}

inline auto GroupKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<GroupKernel>(*this);
}

inline auto GroupKernel::get_type() const -> GateType {
  return TYPE;
}

inline auto GroupKernel::get_type_name() const -> std::string {
  return TYPE_NAME;
}

inline auto GroupKernel::is_group() const -> bool {
  return true;
}

inline auto GroupKernel::bedaggered() const -> bool {
  return false;
}

inline auto GroupKernel::get_cbits() -> CBits& {
  return _get_cbits();
}

inline auto GroupKernel::get_cbits() const -> CBits const& {
  return _get_cbits();
}

inline auto GroupKernel::get_tbits() -> TBits& {
  return _get_tbits();
}

inline auto GroupKernel::get_tbits() const -> TBits const& {
  return _get_tbits();
}

inline auto GroupKernel::get_gates() -> Gates& {
  return gates_;
}

inline auto GroupKernel::get_gates() const -> Gates const& {
  return gates_;
}
}
