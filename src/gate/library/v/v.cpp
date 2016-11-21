#include "../v.hpp"

namespace qc {
constexpr char const* const VCore::TYPE_NAME;

constexpr util::string::Aliases<1> const VCore::ALIASES;

auto VCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<VCore>(*this);
}

constexpr char const* const VDaggerCore::TYPE_NAME;

constexpr util::string::Aliases<4> const VDaggerCore::ALIASES;

auto VDaggerCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<VDaggerCore>(*this);
}
}
