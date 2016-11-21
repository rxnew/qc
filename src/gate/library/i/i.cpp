#include "../i.hpp"

namespace qc {
constexpr char const* const ICore::TYPE_NAME;

constexpr util::string::Aliases<2> const ICore::ALIASES;

auto ICore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<ICore>(*this);
}
}
