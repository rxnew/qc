#include "../s.hpp"

namespace qc {
constexpr char const* const SKernel::TYPE_NAME;

constexpr util::string::Aliases<1> const SKernel::ALIASES;

auto SKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<SKernel>(*this);
}

constexpr char const* const SDaggerKernel::TYPE_NAME;

constexpr util::string::Aliases<4> const SDaggerKernel::ALIASES;

auto SDaggerKernel::clone() const -> std::unique_ptr<GateKernel> {
  return std::make_unique<SDaggerKernel>(*this);
}
}
