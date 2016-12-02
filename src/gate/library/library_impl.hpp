#pragma once

#include "../dagger.hpp"
#include "../../util/string.hpp"
#include "../../debug/error.hpp"

namespace qc {
template <class... Args>
auto make_gate(GateType type, Args&&... args) -> Gate {
#define REGIST(Type) if(Type::TYPE == type) \
    return Gate::make<Type>(std::forward<Args>(args)...)

  REGIST(I);
  REGIST(H);
  REGIST(X);
  REGIST(Y);
  REGIST(Z);
  REGIST(S);
  REGIST(T);
  REGIST(V);
  REGIST(W);
  REGIST(Swap);

#undef REGIST

  return Gate::make_dummy();
}

template <class... Args>
auto make_gate(std::string const& type_name, Args&&... args) -> Gate {
  static constexpr char const* const _err_msg = "Not found gate type '%s'.";

  auto real_type_name = type_name;
  auto dagger = exclude_dagger_tag(real_type_name);

#define REGIST(Type) if(Type::ALIASES == real_type_name) \
    return Gate::make<Type>(dagger, std::forward<Args>(args)...)

  REGIST(I);
  REGIST(H);
  REGIST(X);
  REGIST(Y);
  REGIST(Z);
  REGIST(S);
  REGIST(T);
  REGIST(V);
  REGIST(W);
  REGIST(Swap);

#undef REGIST

  debug::error::issue(util::string::format(_err_msg, type_name));
  return Gate::make_dummy();
}
}
