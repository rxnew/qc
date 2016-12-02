#include "../library.hpp"

namespace qc {
auto decode_alias(std::string const& alias) -> std::string {
  if(X::ALIASES == alias) return X::TYPE_NAME;
  return std::string();
}
}
