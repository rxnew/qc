#include "../h.hpp"

namespace qc {
constexpr GateType const HKernel::TYPE;

constexpr char const* const HKernel::TYPE_NAME;

constexpr util::string::Aliases<2> const HKernel::ALIASES;

auto HKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<HKernel>(*this);
}
}
