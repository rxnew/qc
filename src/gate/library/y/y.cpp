#include "../y.hpp"

namespace qc {
constexpr char const* const YCore::TYPE_NAME;

constexpr util::string::Aliases<1> const YCore::ALIASES;

auto YCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<YCore>(*this);
}
}
