#include "../u.hpp"

#include "../../bedaggered.hpp"

namespace qc {
constexpr GateType const UKernel::TYPE;

constexpr char const* const UKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const UKernel::ALIASES;

auto UKernel::operator=(UKernel const& other) -> UKernel& {
  UnitKernel::operator=(static_cast<UnitKernel const&>(other));
  type_name_ = other.type_name_;
  return *this;
}

auto UKernel::operator=(UKernel&& other) noexcept -> UKernel& {
  UnitKernel::operator=(static_cast<UnitKernel&&>(other));
  type_name_ = other.type_name_;
  return *this;
}

auto UKernel::operator==(UKernel const& other) const -> bool {
  return
    GateKernel::operator==(static_cast<UnitKernel const&>(other)) &&
    BitsWrapperKernel::operator==(other) &&
    std::strcmp(type_name_, other.type_name_) == 0;
}

auto UKernel::operator==(GateKernel const& other) const -> bool {
  return
    GateKernel::operator==(other) &&
    get_cbits() == other.get_cbits() &&
    get_tbits() == other.get_tbits() &&
    get_type_name() == other.get_type_name();
}

auto UKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<UKernel>(*this);
}

auto UKernel::get_type_name() const -> std::string {
  return type_name(type_name_, bedaggered_);
}
}
