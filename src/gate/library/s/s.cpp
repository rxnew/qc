#include "../s.hpp"

namespace qc {
constexpr GateType const SKernel::TYPE;

constexpr char const* const SKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const SKernel::ALIASES;

auto SKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<SKernel>(*this);
}

constexpr GateType const SDaggerKernel::TYPE;

constexpr char const* const SDaggerKernel::TYPE_NAME;

constexpr util::string::Aliases<4> const SDaggerKernel::ALIASES;

auto SDaggerKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<SDaggerKernel>(*this);
}
}
