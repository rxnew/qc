#include "../w.hpp"

#include "../../dagger.hpp"

namespace qc {
constexpr GateType const WKernel::TYPE;

constexpr char const* const WKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const WKernel::ALIASES;

auto WKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<WKernel>(*this);
}

auto WKernel::get_type_name() const -> std::string {
  return type_name(TYPE_NAME, dagger_);
}
}
