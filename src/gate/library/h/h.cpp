#include "../h.hpp"

namespace qc {
constexpr util::string::String const HKernel::TYPE_NAME;

constexpr util::string::Aliases<2> const HKernel::ALIASES;

auto HKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<HKernel>(*this);
}
}
