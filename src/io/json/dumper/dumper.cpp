#include "../dumper.hpp"

#include "../../../circuit.hpp"
#include "../../../debug/issue.hpp"
#include "../../../util/container.hpp"

namespace qc {
namespace io {
auto Json::Dumper::dump() -> void {
  auto operations = _make_json(circuit_);
  os_ << operations.dump();
}

auto Json::Dumper::_make_json(Circuit const& circuit) -> json11::Json {
  auto json_array = json11::Json::array();
  for(auto const& gate : circuit.get_gates()) {
    json_array.push_back(_make_json(gate));
  }
  return json11::Json::object{{"operations", json_array}};
}

auto Json::Dumper::_make_json(Gate const& gate) -> json11::Json {
  if(!gate.is_group()) return _make_json_object(gate);
  auto json_array = json11::Json::array();
  for(auto const& gate_s : gate.get_gates()) {
    json_array.push_back(_make_json(gate_s));
  }
  return json11::Json(json_array);
}

auto Json::Dumper::_make_json_object(Gate const& gate) -> json11::Json {
  auto controls_json_array = json11::Json::array();
  auto targets_json_array = json11::Json::array();
  for(auto const& cbit : gate.get_cbits()) {
    controls_json_array.push_back(static_cast<int>(cbit.get_no()));
  }
  for(auto const& tbit : gate.get_tbits()) {
    targets_json_array.push_back(static_cast<int>(tbit.get_no()));
  }
  return json11::Json::object{
    {"type",     gate.get_type_name()},
    {"controls", controls_json_array},
    {"targets",  targets_json_array}
  };
}
}
}
