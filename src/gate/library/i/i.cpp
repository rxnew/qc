#include "../i.hpp"

namespace qc {
constexpr GateType const IKernel::TYPE;

constexpr char const* const IKernel::TYPE_NAME;

constexpr util::string::Aliases<2> const IKernel::ALIASES;

auto IKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<IKernel>(*this);
}
}
