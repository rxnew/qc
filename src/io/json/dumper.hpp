/**
 * @file dumper.hpp
 * @brief header of qc::io::Json::Dumper class
 */

#pragma once

#include "json11.hpp"

#include "../json.hpp"

namespace qc {
namespace io {
class Json::Dumper {
 public:
  Dumper(Circuit const& circuit, std::ostream& os);
  ~Dumper() = default;

  auto dump() -> void;

 private:
  auto _make_json(std::string const& format, Circuit const& circuit)
    -> json11::Json;
  auto _make_json(Circuit const& circuit) -> json11::Json;
  auto _make_json(Gate const& gate) -> json11::Json;
  auto _make_json_object(Gate const& gate) -> json11::Json;

  Circuit const& circuit_;
  std::ostream& os_;
};
}
}

#include "dumper/dumper_impl.hpp"
