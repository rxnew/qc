#pragma once

#include "../../../gate.hpp"
#include "../../gate_private.hpp"

namespace qc {
template <class... Args>
X::Impl::Impl(Args&&... args) : Gate::Impl(std::forward<Args>(args)...) {}

inline auto X::Impl::clone() const -> std::unique_ptr<Impl> {
  return std::make_unique<Impl>(*this);
}

inline auto X::Impl::get_type_name() const -> decltype(TYPE_NAME)& {
  return TYPE_NAME;
}
}
