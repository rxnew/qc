#include "../w.hpp"

namespace qc {
constexpr char const* const WKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const WKernel::ALIASES;

auto WKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<WKernel>(*this);
}

constexpr char const* const WDaggerKernel::TYPE_NAME;

constexpr util::string::Aliases<4> const WDaggerKernel::ALIASES;

auto WDaggerKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<WDaggerKernel>(*this);
}
}
