#include "../swap.hpp"

namespace qc {
constexpr GateType const SwapKernel::TYPE;

constexpr char const* const SwapKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const SwapKernel::ALIASES;

auto SwapKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<SwapKernel>(*this);
}
}
