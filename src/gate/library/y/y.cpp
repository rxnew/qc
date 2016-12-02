#include "../y.hpp"

namespace qc {
constexpr GateType const YKernel::TYPE;

constexpr char const* const YKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const YKernel::ALIASES;

auto YKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<YKernel>(*this);
}
}
