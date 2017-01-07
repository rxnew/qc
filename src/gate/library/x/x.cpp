#include "../x.hpp"

namespace qc {
constexpr GateType const XKernel::TYPE;

constexpr char const* const XKernel::TYPE_NAME;

constexpr util::string::Aliases<2> const XKernel::ALIASES;

auto XKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<XKernel>(*this);
}
}
