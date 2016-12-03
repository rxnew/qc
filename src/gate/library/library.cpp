#include "../library.hpp"

namespace qc {
auto decode_alias(std::string const& alias, bool assert_flag) -> std::string {
  auto real_alias = alias;
  auto bedaggered = exclude_bedaggered_tag(real_alias);

#define REGIST(Type) if(Type::ALIASES == real_alias) \
    return type_name(Type::TYPE_NAME, bedaggered)

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
