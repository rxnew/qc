#include "../t.hpp"

namespace qc {
constexpr util::string::String const TKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const TKernel::ALIASES;

auto TKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<TKernel>(*this);
}

constexpr util::string::String const TDaggerKernel::TYPE_NAME;

constexpr util::string::Aliases<4> const TDaggerKernel::ALIASES;

auto TDaggerKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<TDaggerKernel>(*this);
}
}
