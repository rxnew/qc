#include "../x.hpp"

namespace qc {
constexpr char const* const XCore::TYPE_NAME;

constexpr util::string::Aliases<5> const XCore::ALIASES;

auto XCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<XCore>(*this);
}
}
