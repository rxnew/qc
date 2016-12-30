#include "../json.hpp"
#include "parser.hpp"
//#include "dumper.hpp"

#include "../../circuit.hpp"

namespace qc {
namespace io {
Json::Messages const Json::_err_msgs = {
  {"E000", "Illegal format. Unknown terminology."},
  {"E010", "Illegal format. Incomplete description of '%s'."},
  {"E020", "Illegal format. The format of parameters of the gate is 'formal=actual'."},
  {"E021", "Illegal format. Parameters of the gate is different."}
};

Json::Messages const Json::_warn_msgs = {
  {"W000",  "'%s' is not supported yet."},
  {"W010",  "The gate, '%s' is not supported yet."},
  {"W020",  "The output line, '%s' is duplicated."},
  {"W100",  "This circuit contains gates other than MCT (multiple-control Toffoli)."}
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
  //Dumper(circuit, os).dump();
}
}
}
