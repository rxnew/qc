#pragma once

#include <fstream>
#include <tuple>

#include "circuit.hpp"

namespace qc {
using BitListTuple = std::tuple<CbitList, TbitList>;

class FileManager {
 private:
  using strings = std::vector<std::string>;

  static auto _divideIntoGroups(const std::string& line) -> strings;
  static auto _getGateString(const std::string& str) -> std::string;
  static auto _getBitStrings(const std::string& str) -> strings;
  static auto _getOptionStrings(const std::string& str) -> strings;
  static auto _getCbit(const std::string& bit_str) -> Cbit;
  static auto _getTbit(const std::string& bit_str) -> Tbit;
  static auto _getBits(const strings& bit_strs) -> BitListTuple;
  static auto _getGate(const std::string& gate_str, const BitListTuple& bits)
    -> GatePtr;

 public:
  static auto open(const std::string& filename) -> Circuit;
  static auto open(const char* filename) -> Circuit;
};

inline auto FileManager::open(const char* filename) -> Circuit {
  return FileManager::open(std::string(filename));
}
}
