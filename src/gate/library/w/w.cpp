#include "../w.hpp"

namespace qc {
constexpr char const* const WCore::TYPE_NAME;

constexpr util::string::Aliases<1> const WCore::ALIASES;

auto WCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<WCore>(*this);
}

constexpr char const* const WDaggerCore::TYPE_NAME;

constexpr util::string::Aliases<4> const WDaggerCore::ALIASES;

auto WDaggerCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<WDaggerCore>(*this);
}
}
