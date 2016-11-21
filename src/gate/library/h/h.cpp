#include "../h.hpp"

namespace qc {
constexpr char const* const HCore::TYPE_NAME;

constexpr util::string::Aliases<2> const HCore::ALIASES;

auto HCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<HCore>(*this);
}
}
