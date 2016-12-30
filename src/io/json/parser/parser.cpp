#include "../parser.hpp"

#include <queue>

#include "json11.hpp"

#include "../../../circuit.hpp"
#include "../../../gate/library/x.hpp"

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

  //_parse(json);

  return std::move(circuit_);
}
}
}
