#pragma once

namespace qc {
template <class T, class... Args, class>
UKernel::UKernel(T&& arg, Args&&... args)
  : UnitKernel(std::forward<T>(arg), std::forward<Args>(args)...),
    type_name_(TYPE_NAME) {}

template <class... Args>
UKernel::UKernel(char const* const type_name, Args&&... args)
  : UnitKernel(std::forward<Args>(args)...), type_name_(type_name) {}

template <class... Args>
UKernel::UKernel(std::string const& type_name, Args&&... args)
  : UnitKernel(std::forward<Args>(args)...), type_name_(type_name.c_str()) {}

inline UKernel::UKernel(UKernel const& other)
  : UnitKernel(static_cast<UnitKernel const&>(other)),
    type_name_(other.type_name_) {}

inline UKernel::UKernel(UKernel&& other) noexcept
  : UnitKernel(static_cast<UnitKernel&&>(other)),
    type_name_(other.type_name_) {}

inline auto UKernel::operator!=(UKernel const& other) const -> bool {
  return !(*this == other);
}

inline auto UKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}

inline auto UKernel::get_type() const -> GateType {
  return TYPE;
}
}
