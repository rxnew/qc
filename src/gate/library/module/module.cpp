#include "../module.hpp"

namespace qc {
constexpr char const* const Module::TYPE_NAME = "Module";
constexpr util::string::Aliases<5> const Module::ALIASES = {
  "module",
  "macrogate",
  "gatearray",
  "step",
  "pqgate"
};

auto Module::Impl::print(std::ostream& os) const -> void {
  for(auto const& inner : inners_) {
    inner.print(os);
    os << std::endl;
  }
}

auto Module::Impl::_get_cbits() const -> CBits& {
  m_cbits_.clear();
  for(auto const& inner : inners_) {
    for(auto const& cbit : inner.get_cbits()) {
      m_cbits_.insert(cbit);
    }
  }
  return m_cbits_;
}

auto Module::Impl::_get_tbits() const -> TBits& {
  m_tbits_.clear();
  for(auto const& inner : inners_) {
    for(auto const& tbit : inner.get_tbits()) {
      m_tbits_.insert(tbit);
    }
  }
  return m_tbits_;
}
}
