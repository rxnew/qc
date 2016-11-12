#include "../io.hpp"
#include "io_private.hpp"

namespace qc {
namespace io {
auto input(Circuit& circuit, const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void {
  auto extension = util::string::getExtension(filename);
  auto if_exc = io::_getNotSupportFormatException(extension, "qc::io::input");
  if(extension == Qo::extension)   return Qo::input(circuit, filename);
  if(extension == Blif::extension) return Blif::input(circuit, filename);
  if(extension == Esop::extension) return Esop::input(circuit, filename);
  throw io::_getUnknownFormatException(extension);
}

auto output(const Circuit& circuit, const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void {
  auto extension = util::string::getExtension(filename);
  auto if_exc = io::_getNotSupportFormatException(extension, "qc::io::output");
  if(extension == Qo::extension)   return Qo::output(circuit, filename);
  if(extension == Blif::extension) return Blif::output(circuit, filename);
  if(extension == Esop::extension) return Esop::output(circuit, filename);
  throw io::_getUnknownFormatException(extension);
}

auto open(const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> Circuit {
  auto basename = qc::util::string::basename(filename);
  Circuit circuit(qc::util::string::excludeExtension(basename));
  io::input(circuit, filename);
  return std::move(circuit);
}
}
}
