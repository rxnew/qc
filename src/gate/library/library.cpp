/**
 * @file library.cpp
 * @brief implementation about library gates
 */

#include "../library.hpp"

namespace qc {
auto getGateType(const std::string& str) -> const std::string& {
  static const std::multimap<std::string, std::string> aliases = {
    {"X", "Not"},
    {"X", "Mct"},
    {"VPlus", "VDagger"},
    {"S", "P"},
    {"Hadamard", "H"}
  };

  for(const auto& alias : aliases) {
    if(util::string::equalCaseInsensitive(str, alias.second)) {
      return alias.first;
    }
  }
  return str;
}
}
