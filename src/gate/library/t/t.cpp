#include "../t.hpp"

namespace qc {
constexpr char const* const TCore::TYPE_NAME;

constexpr util::string::Aliases<1> const TCore::ALIASES;

auto TCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<TCore>(*this);
}

constexpr char const* const TDaggerCore::TYPE_NAME;

constexpr util::string::Aliases<4> const TDaggerCore::ALIASES;

auto TDaggerCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<TDaggerCore>(*this);
}
}
