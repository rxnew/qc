#pragma once

#include "../../util/string.hpp"
#include "../../debug/error.hpp"

namespace qc {
template <class... Args>
auto make_gate(std::string const& type_name, Args&&... args)
  -> Gate {
  static constexpr char const* const _err_msg = "Not found gate type '%s'.";

  if(type_name == "X") return Gate::make<X>(std::forward<Args>(args)...);

  debug::error::issue(util::string::format(_err_msg, type_name));
  return Gate::make_dummy();
}
}
