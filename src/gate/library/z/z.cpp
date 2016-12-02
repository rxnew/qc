#include "../z.hpp"

namespace qc {
constexpr char const* const ZKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const ZKernel::ALIASES;

auto ZKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<ZKernel>(*this);
}
}
