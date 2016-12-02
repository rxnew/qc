#include "../v.hpp"

#include "../../dagger.hpp"

namespace qc {
constexpr GateType const VKernel::TYPE;

constexpr char const* const VKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const VKernel::ALIASES;

auto VKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<VKernel>(*this);
}

auto VKernel::get_type_name() const -> std::string {
  return type_name(TYPE_NAME, dagger_);
}
}
