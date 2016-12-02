#include "../v.hpp"

namespace qc {
constexpr GateType const VKernel::TYPE;

constexpr char const* const VKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const VKernel::ALIASES;

auto VKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<VKernel>(*this);
}

constexpr GateType const VDaggerKernel::TYPE;

constexpr char const* const VDaggerKernel::TYPE_NAME;

constexpr util::string::Aliases<4> const VDaggerKernel::ALIASES;

auto VDaggerKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<VDaggerKernel>(*this);
}
}
