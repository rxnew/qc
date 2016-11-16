/**
 * @file aliases.cpp
 * @brief implementation of aliases
 */

#include "../aliases.hpp"

namespace qc {
std::unordered_map<util::string::istring, std::string> const
gate_type_aliases = {
  {"Not",     "X"},
  {"Cnot",    "X"},
  {"Mct",     "X"},
  {"VDagger", "VPlus"},
  {"P",       "S"},
  {"H",       "Hadamard"}
};
}
