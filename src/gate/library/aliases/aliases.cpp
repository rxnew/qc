/**
 * @file aliases.cpp
 * @brief implementation of aliases
 */

#include "../aliases.hpp"

namespace qc {
const std::multimap<std::string, std::string> gate_type_aliases = { 
  {"X", "Not"},
  {"X", "Mct"},
  {"VPlus", "VDagger"},
  {"S", "P"},
  {"Hadamard", "H"}
};
}
