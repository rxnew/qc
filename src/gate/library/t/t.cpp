#include "../t.hpp"

#include "../../dagger.hpp"

namespace qc {
constexpr GateType const TKernel::TYPE;

constexpr char const* const TKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const TKernel::ALIASES;

auto TKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<TKernel>(*this);
}

auto TKernel::get_type_name() const -> std::string {
  return type_name(TYPE_NAME, dagger_);
}
}
