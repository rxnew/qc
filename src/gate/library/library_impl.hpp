#pragma once

#include "../../util/string.hpp"
#include "../../debug/error.hpp"

namespace qc {
template <class... Args>
auto make_gate(std::string const& type_name, Args&&... args)
  -> Gate {
  static constexpr char const* const _err_msg = "Not found gate type '%s'.";

  if(X::ALIASES == type_name) {
    return Gate::make<X>(std::forward<Args>(args)...);
  }

  debug::error::issue(util::string::format(_err_msg, type_name));
  return Gate::make_dummy();
}

auto decode_alias(util::string::String const& alias)
  -> util::string::String const& {
  if(X::ALIASES == alias) return X::TYPE_NAME;

  static constexpr util::string::String const dummy = "";
  return dummy;
}
}
