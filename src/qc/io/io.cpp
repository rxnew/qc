#include "io.hpp"

namespace qc {
namespace io {
auto input(Circuit& circuit, const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void {
  auto extension = io::getExtension(filename);
  if(extension == "qo")   return Qo::input(circuit, filename);
  if(extension == "esop") return Esop::input(circuit, filename);
  throw std::ios_base::failure("Unknown extension: '" + extension + "'.");
}

auto input(Circuit& circuit, const char* const filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void {
  return io::input(circuit, filename);
}

auto getExtension(const std::string& filename) -> std::string {
  auto strs = util::string::split(filename, '.', false);
  if(strs.size() < 2) return std::string();
  return std::move(strs.back());
}
}
}
