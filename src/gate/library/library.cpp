#include "../library.hpp"

namespace qc {
auto make_gate(GateType type,
               std::initializer_list<CBit> cbits,
               std::initializer_list<TBit> tbits) -> Gate {
  return make_gate(type, false, cbits, tbits);
}

auto make_gate(GateType type,
               bool bedaggered,
               std::initializer_list<CBit> cbits,
               std::initializer_list<TBit> tbits) -> Gate {
  return make_gate(type, bedaggered, CBits(cbits), TBits(tbits));
}

auto make_gate(std::string const& type_name,
               std::initializer_list<CBit> cbits,
               std::initializer_list<TBit> tbits) -> Gate {
  return make_gate(type_name, CBits(cbits), TBits(tbits));
}

auto decode_alias(std::string const& alias, bool assert_flag) -> std::string {
  auto real_alias = alias;
  auto bedaggered = exclude_bedaggered_tag(real_alias);

#define REGIST(Type) if(Type::ALIASES == real_alias) \
    return type_name(Type::TYPE_NAME, bedaggered)

  REGIST(U);
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

  assert(!assert_flag);
  return std::string();
}
}
