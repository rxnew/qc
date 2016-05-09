/**
 * @file library.cpp
 * @brief implementation about library gates
 */

#include "../library.hpp"

#include "aliases.hpp"

namespace qc {
auto getGateTypeName(const std::string& str) -> const std::string& {
  for(const auto& alias : qc::gate_type_aliases) {
    if(util::string::equalCaseInsensitive(str, alias.second)) {
      return alias.first;
    }
  }
  return str;
}
}
