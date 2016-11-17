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
  if(Module::ALIASES == type_name) {
    return Gate::make<Module>(std::forward<Args>(args)...);
  }

  debug::error::issue(util::string::format(_err_msg, type_name));
  return Gate::make_dummy();
}

constexpr auto decode_alias(char const* const alias) -> char const* const {
  if(X::ALIASES == alias)      return X::TYPE_NAME;
  if(Module::ALIASES == alias) return Module::TYPE_NAME;
  return "";
}
}
