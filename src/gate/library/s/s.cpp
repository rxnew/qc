#include "../s.hpp"

namespace qc {
constexpr char const* const SCore::TYPE_NAME;

constexpr util::string::Aliases<1> const SCore::ALIASES;

auto SCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<SCore>(*this);
}

constexpr char const* const SDaggerCore::TYPE_NAME;

constexpr util::string::Aliases<4> const SDaggerCore::ALIASES;

auto SDaggerCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<SDaggerCore>(*this);
}
}
