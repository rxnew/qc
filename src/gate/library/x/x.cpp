#include "../x.hpp"

namespace qc {
constexpr util::string::String const XKernel::TYPE_NAME;

constexpr util::string::Aliases<5> const XKernel::ALIASES;

auto XKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<XKernel>(*this);
}
}
