#include "../z.hpp"

namespace qc {
constexpr char const* const ZCore::TYPE_NAME;

constexpr util::string::Aliases<1> const ZCore::ALIASES;

auto ZCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<ZCore>(*this);
}
}
