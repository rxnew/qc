#include "../blif.hpp"
#include "parser.hpp"
#include "dumper.hpp"

namespace qc {
namespace io {
const std::string Blif::extension = ".blif";

const Blif::Messages Blif::_err_msgs = {
  {"E000", "Illegal format. Unknown terminology."},
  {"E010", "Illegal format. Incomplete description of '%s'."},
  {"E020", "Illegal format. The format of parameters of the gate is 'formal=actual'."},
  {"E021", "Illegal format. Parameters of the gate is different."}
};

const Blif::Messages Blif::_warn_msgs = {
  {"W000",  "'%s' is not supported yet."},
  {"W010",  "The gate, '%s' is not supported yet."},
  {"W020",  "The output line, '%s' is duplicated."},
  {"W100",  "This circuit contains gates other than MCT (multiple-control Toffoli)."}
};

auto Blif::input(Circuit& circuit, const std::string& filename)
  throw(IfExc, std::ios_base::failure) -> void {
  circuit = std::move(Parser(filename).parse());
}

auto Blif::output(const Circuit& circuit, const std::string& filename)
  throw(std::ios_base::failure) -> void {
  std::ofstream ofs(util::string::addExtension(filename, Blif::extension));
  if(ofs.fail()) throw std::ios_base::failure("Cannot open file.");
  Blif::print(circuit, ofs);
}

auto Blif::open(const std::string& filename)
  throw(IfExc, std::ios_base::failure) -> Circuit {
  auto basename = qc::util::string::basename(filename);
  Circuit circuit(qc::util::string::excludeExtension(basename));
  Blif::input(circuit, filename);
  return std::move(circuit);
}

auto Blif::print(const Circuit& circuit, std::ostream& os) -> void {
  Dumper(circuit, os).dump();
}
}
}
