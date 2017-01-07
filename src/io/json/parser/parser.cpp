#include "../parser.hpp"

#include <queue>

#include "../../../circuit.hpp"
#include "../../../gate/group.hpp"
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

  _check_format_type(json);

  if(!json["circuit"].is_null()) json = json["circuit"];

  return _parse(json);
}

auto Json::Parser::_parse(json11::Json const& json)
  throw(IfExc) -> Circuit {
  auto circuit = Circuit();
  for(auto const& gate : json["gates"].array_items()) {
    circuit.add_gate(_make_gate(gate));
  }
  return circuit;
}

auto Json::Parser::_make_gate(json11::Json const& json)
  throw(IfExc) -> Gate {
  if(json.is_object()) {
    auto const& type_name = _get_type_name(json);
    auto cbits = _get_cbits(json);
    auto tbits = _get_tbits(json);
    return make_gate(type_name, cbits, tbits);
  }
  auto group = make_group();
  for(auto const& gate : json.array_items()) {
    group.add_gate(_make_gate(gate));
  }
  return group;
}

auto Json::Parser::_get_type_name(json11::Json const& json)
  throw(IfExc) -> std::string const& {
  if(!json["type"].is_string()) _error("E000");
  return json["type"].string_value();
}

auto Json::Parser::_get_cbits(json11::Json const& json)
  throw(IfExc) -> CBits {
  auto cbits = CBits();
  auto const& controls = json["controls"];
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
  auto const& targets = json["targets"];
  if(!targets.is_array()) _error("E001");
  for(auto const& bit_no : targets.array_items()) {
    if(!bit_no.is_number()) _error("E002");
    tbits.insert(CBit(static_cast<BitNo>(bit_no.int_value())));
  }
  return tbits;
}

auto Json::Parser::_check_format_type(json11::Json const& json)
  throw(IfExc) -> void {
  if(json["format"].is_null()) {
    _warn("W100");
  }
  else if(json["format"].string_value() != format_type) {
    _error("E100", json["format"].string_value());
  }
}
}
}
