#include "../s.hpp"

#include "../../dagger.hpp"

namespace qc {
constexpr GateType const SKernel::TYPE;

constexpr char const* const SKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const SKernel::ALIASES;

auto SKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<SKernel>(*this);
}

auto SKernel::get_type_name() const -> std::string {
  return type_name(TYPE_NAME, dagger_);
}
}
