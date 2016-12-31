#include "../json.hpp"
#include "parser.hpp"
#include "dumper.hpp"

#include "../../circuit.hpp"

namespace qc {
namespace io {
Json::Messages const Json::_err_msgs = {
  {"E000", "Illegal format. The operation type is not a string."},
  {"E001", "Illegal format. Controls or targets is not an array."},
  {"E002", "Illegal format. The control or target is not a number."}
};

Json::Messages const Json::_warn_msgs = {
};

auto Json::input(Circuit& circuit, std::string const& filename)
  throw(IfExc, std::ios_base::failure) -> void {
  circuit = Parser(filename).parse();
}

auto Json::output(Circuit const& circuit, std::string const& filename)
  throw(std::ios_base::failure) -> void {
  auto ofs = std::ofstream(util::string::add_extension(filename, extension));
  if(ofs.fail()) throw std::ios_base::failure("Cannot open file.");
  print(circuit, ofs);
}

auto Json::open(std::string const& filename)
  throw(IfExc, std::ios_base::failure) -> Circuit {
  auto const basename = util::string::basename(filename);
  auto circuit = Circuit(util::string::exclude_extension(basename));
  input(circuit, filename);
  return circuit;
}

auto Json::print(Circuit const& circuit, std::ostream& os) -> void {
  Dumper(circuit, os).dump();
}
}
}
