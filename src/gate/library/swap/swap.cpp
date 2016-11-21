#include "../swap.hpp"

namespace qc {
constexpr char const* const SwapCore::TYPE_NAME;

constexpr util::string::Aliases<1> const SwapCore::ALIASES;

auto SwapCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<SwapCore>(*this);
}
}
