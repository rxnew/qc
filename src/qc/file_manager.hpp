#pragma once

#include <fstream>

#include "string_helper.hpp"

#include "circuit.hpp"

namespace qc {
class FileManager {
 private:
  static auto _ignoreComments(const std::vector<std::string>& elems)
    -> std::vector<std::string>;
  static auto _verifyFormat(const std::vector<std::string>& elems) -> bool;
  static auto _getCbit(std::string bit) -> Cbit;
  static auto _getTbit(std::string bit) -> Tbit;
  static auto _getGate(const std::vector<std::string>& elems) -> GatePtr;

 public:
  static auto open(const std::string& filename) -> Circuit;
  static auto open(const char* filename) -> Circuit;
};

inline auto FileManager::open(const char* filename) -> Circuit {
  return FileManager::open(std::string(filename));
}
}
