#include "esop.hpp"

namespace qc {
namespace io {
std::array<std::string, 2> Esop::_err_msgs = {
  "Header format is illegal.",
  "Terms format is illegal."
};

auto Esop::_setCount(Counts& counts, const std::string& line)
  throw(IfExc) -> void {
  auto data = util::string::split(line);
  if(data.size() != 2) throw IfExc(Esop::_err_msgs[0]);
  if(data[0] == ".i")      counts["input"]  = std::stoi(data[1]);
  else if(data[0] == ".o") counts["output"] = std::stoi(data[1]);
  else if(data[0] == ".p") counts["term"]   = std::stoi(data[1]);
  else if(data[0] != ".type" || data[1] != "esop") {
    throw IfExc(Esop::_err_msgs[0]);
  }
}

auto Esop::_getCounts(std::ifstream& ifs)
  throw(IfExc) -> Counts {
  Counts counts;
  std::string line;
  while(std::getline(ifs, line) && counts.size() < 3) {
    if(!Esop::_isCommentLine(line)) Esop::_setCount(counts, line);
  }
  if(counts.size() != 3) throw IfExc(Esop::_err_msgs[0]);
  return std::move(counts);
}

auto Esop::_getCbits(const std::string& str)
  throw(IfExc) -> CbitList {
  CbitList cbits;
  for(int i = 0; i < static_cast<int>(str.size()); i++) {
    if(str[i] == '1')      cbits.emplace(static_cast<Bitno>(i), true);
    else if(str[i] == '0') cbits.emplace(static_cast<Bitno>(i), false);
    else if(str[i] != '-') throw IfExc(Esop::_err_msgs[1]);
  }
  return std::move(cbits);
}

auto Esop::_getTbits(const std::string& str, int first)
  throw(IfExc) -> TbitList {
  TbitList tbits;
  for(int i = 0; i < static_cast<int>(str.size()); i++) {
    if(str[i] == '1') tbits.emplace(static_cast<Bitno>(i + first));
    else if(str[i] == '0') throw IfExc(Esop::_err_msgs[1]);
  }
  return std::move(tbits);
}

auto Esop::_getGate(const std::string& line, const Counts& counts)
  throw(IfExc) -> GatePtr {
  auto data = util::string::split(line);
  if(data.size() != 2 ||
     data[0].size() != counts.at("input") ||
     data[1].size() != counts.at("output")) {
    throw IfExc(Esop::_err_msgs[1]);
  }
  auto cbits = Esop::_getCbits(data[0]);
  auto tbits = Esop::_getTbits(data[1], counts.at("input"));
  return std::move(GatePtr(new Not(cbits, tbits)));
}

auto Esop::open(const std::string& filename) -> Circuit {
  Circuit circuit;

  std::ifstream ifs(filename);
  std::string line;

  assert(!ifs.fail());

  auto counts = Esop::_getCounts(ifs);

  while(std::getline(ifs, line)) {
    if(Esop::_isCommentLine(line)) continue;
    if(Esop::_isEndLine(line)) break;
    auto gate = Esop::_getGate(line, counts);
    assert(gate);
    circuit.addGate(gate);
  }

  assert(counts["term"] == circuit.getGateCount());

  return std::move(circuit);
}
}
}
