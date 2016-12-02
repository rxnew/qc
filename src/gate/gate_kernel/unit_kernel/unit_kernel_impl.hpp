#pragma once

namespace qc {
template <class... Args>
inline UnitKernel::UnitKernel(Args&&... args)
  : BitsWrapperKernel(std::forward<Args>(args)...) {}

inline UnitKernel::UnitKernel(UnitKernel const& other)
  : BitsWrapperKernel(other) {}

inline UnitKernel::UnitKernel(UnitKernel&& other) noexcept
  : BitsWrapperKernel(std::move(other)) {}

inline auto UnitKernel::operator=(UnitKernel const& other) -> UnitKernel& {
  BitsWrapperKernel::operator=(other);
  return *this;
}

inline auto UnitKernel::operator=(UnitKernel&& other) noexcept -> UnitKernel& {
  BitsWrapperKernel::operator=(std::move(other));
  return *this;
}

inline auto UnitKernel::operator==(UnitKernel const& other) const -> bool {
  return GateKernel::operator==(other) && BitsWrapperKernel::operator==(other);
}

inline auto UnitKernel::operator!=(UnitKernel const& other) const -> bool {
  return !(*this == other);
}

inline auto UnitKernel::operator==(GateKernel const& other) const -> bool {
  return
    GateKernel::operator==(other) &&
    get_cbits() == other.get_cbits() &&
    get_tbits() == other.get_tbits();
}

inline auto UnitKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}

inline auto UnitKernel::is_group() const -> bool {
  return false;
}

inline auto UnitKernel::get_cbits() -> CBits& {
  return cbits_;
}

inline auto UnitKernel::get_cbits() const -> CBits const& {
  return cbits_;
}

inline auto UnitKernel::get_tbits() -> TBits& {
  return tbits_;
}

inline auto UnitKernel::get_tbits() const -> TBits const& {
  return tbits_;
}
}
