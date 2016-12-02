#include "../y.hpp"

namespace qc {
constexpr util::string::String const YKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const YKernel::ALIASES;

auto YKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<YKernel>(*this);
}
}
