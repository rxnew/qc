#include "../io.hpp"
#include "io_private.hpp"

#include "../forward_declarations.hpp"
#include "../circuit.hpp"
#include "../util/string.hpp"

namespace qc {
namespace io {
auto input(Circuit& circuit, std::string const& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void {
  auto extension = util::string::get_extension(filename);
  auto if_exc = _get_not_support_format_exception(extension, "qc::io::input");
  if(extension == Qo::extension)   return Qo::input(circuit, filename);
  if(extension == Blif::extension) return Blif::input(circuit, filename);
  if(extension == Esop::extension) return Esop::input(circuit, filename);
  throw _get_unknown_format_exception(extension);
}

auto output(Circuit const& circuit, std::string const& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void {
  auto extension = util::string::get_extension(filename);
  auto if_exc = _get_not_support_format_exception(extension, "qc::io::output");
  if(extension == Qo::extension)   return Qo::output(circuit, filename);
  if(extension == Blif::extension) return Blif::output(circuit, filename);
  if(extension == Esop::extension) return Esop::output(circuit, filename);
  throw _get_unknown_format_exception(extension);
}

auto open(std::string const& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> Circuit {
  auto basename = util::string::basename(filename);
  auto circuit = Circuit(util::string::exclude_extension(basename));
  input(circuit, filename);
  return circuit;
}

auto convert(std::string const& input_filename,
             std::string const& output_filename)
  throw(exc::IllegalFormatException, std::ios_base::failure)-> void {
  io::output(io::open(input_filename), output_filename);
}
}
}
