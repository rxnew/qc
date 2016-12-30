#include "../parser.hpp"

#include <queue>

#include "../../../circuit.hpp"
#include "../../../gate/library.hpp"

namespace qc {
namespace io {
auto Json::Parser::parse()
  throw(IfExc, std::ios_base::failure) -> Circuit {
  ifs_.open(filename_);

  if(ifs_.fail()) throw std::ios_base::failure("Cannot open file.");

  auto buf = std::string();
  auto tmp = std::string();
  while(std::getline(ifs_, tmp)) buf += tmp;

  ifs_.close();

  auto err = std::string();
  auto json = json11::Json::parse(buf, err);

  return _parse(json);
}

auto Json::Parser::_parse(json11::Json const& json)
  throw(IfExc) -> Circuit {
  auto circuit = Circuit();
  for(auto const& operation : json["operations"].array_items()) {
    auto const& type_name = _get_type_name(operation);
    auto cbits = _get_cbits(operation);
    auto tbits = _get_tbits(operation);
    circuit.add_gate(make_gate(type_name, cbits, tbits));
  }
  return circuit;
}

auto Json::Parser::_get_type_name(json11::Json const& json)
  throw(IfExc) -> std::string const& {
  if(!json["type"].is_string()) _error("E000");
  return json["type"].string_value();
}

auto Json::Parser::_get_cbits(json11::Json const& json)
  throw(IfExc) -> CBits {
  auto cbits = CBits();
  auto const& controls = json["bits"]["controls"];
  if(controls.is_null()) return CBits();
  if(!controls.is_array()) _error("E001");
  for(auto const& bit_no : controls.array_items()) {
    if(!bit_no.is_number()) _error("E002");
    cbits.insert(CBit(static_cast<BitNo>(bit_no.int_value())));
  }
  return cbits;
}

auto Json::Parser::_get_tbits(json11::Json const& json)
  throw(IfExc) -> TBits {
  auto tbits = TBits();
  auto const& targets = json["bits"]["targets"];
  if(!targets.is_array()) _error("E001");
  for(auto const& bit_no : targets.array_items()) {
    if(!bit_no.is_number()) _error("E002");
    tbits.insert(CBit(static_cast<BitNo>(bit_no.int_value())));
  }
  return tbits;
}
}
}
