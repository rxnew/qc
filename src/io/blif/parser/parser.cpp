#include "../parser.hpp"

#include <queue>

namespace qc {
namespace io {
auto Blif::Parser::_init() -> void {
  this->model_name_ = util::string::excludeExtension(this->filename_);
  this->input_wire_names_.clear();
  this->output_wire_names_.clear();
  this->lines_counter_ = 0;
  this->bit_map_.clear();
  this->bit_counter_ = 0;
  this->middle_gate_map_.clear();
}

auto Blif::Parser::_parseLine(std::ifstream& ifs)
  throw(IfExc) -> bool {
  std::getline(ifs, this->line_);
  this->lines_counter_++;
  this->line_ = util::string::trimComments(this->line_, '#');
  const auto tokens = util::string::split(this->line_);

  // 空行 or コメント行
  if(tokens.empty()) return true;

  if(tokens[0] == ".end") return false;

  if(tokens[0] == ".model")        this->_parseModelName(tokens);
  else if(tokens[0] == ".inputs")  this->_parseInputs(tokens);
  else if(tokens[0] == ".outputs") this->_parseOutputs(tokens);
  else if(tokens[0] == ".clock")   this->_parseClocks(tokens);
  else if(tokens[0] == ".gate")    this->_parseGate(tokens);
  else throw IfExc(Blif::_err_msgs.at("E000"));

  return true;
}

auto Blif::Parser::_parseModelName(const Tokens& tokens)
  throw(IfExc) -> void {
  if(tokens.size() < 2) throw IfExc(Blif::_err_msgs.at("E100"));

  this->model_name_ = tokens[1];
}

auto Blif::Parser::_parseInputs(const Tokens& tokens)
  throw(IfExc) -> void {
  if(tokens.size() < 2) throw IfExc(Blif::_err_msgs.at("E101"));

  for(auto i = 1; i < static_cast<int>(tokens.size()); i++) {
    this->input_wire_names_.insert(tokens[i]);
    this->bit_map_[tokens[i]] = this->bit_counter_++;
  }
}

auto Blif::Parser::_parseOutputs(const Tokens& tokens)
  throw(IfExc) -> void {
  if(tokens.size() < 2) throw IfExc(Blif::_err_msgs.at("E102"));

  for(auto i = 1; i < static_cast<int>(tokens.size()); i++) {
    this->output_wire_names_.insert(tokens[i]);
    this->bit_map_[tokens[i]] = this->bit_counter_++;
  }
}

auto Blif::Parser::_parseClocks(const Tokens& tokens)
  throw(IfExc) -> void {
  if(tokens.size() < 2) throw IfExc(Blif::_err_msgs.at("E103"));

  this->_warn("W000");
}

auto Blif::Parser::_parseGate(const Tokens& tokens)
  throw(IfExc) -> void {
  if(tokens.size() < 4) throw IfExc(Blif::_err_msgs.at("E104"));

  const auto gate_name = tokens[1];
  if(gate_name == "nand2") this->_createGateNand2(tokens);
  else this->_warn("W100", gate_name);
}

auto Blif::Parser::_parseMlatch(const Tokens& tokens)
  throw(IfExc) -> void {
  if(tokens.size() < 2) throw IfExc(Blif::_err_msgs.at("E105"));

  this->_warn("W002");
}

auto Blif::Parser::_parseLatch(const Tokens& tokens)
  throw(IfExc) -> void {
  if(tokens.size() < 2) throw IfExc(Blif::_err_msgs.at("E106"));

  this->_warn("W003");
}

auto Blif::Parser::_parseGateParams(const std::string& token)
  throw(IfExc) ->  std::pair<std::string, std::string> {
  const auto terms = util::string::split(token, '=');

  if(terms.size() != 2) throw IfExc(Blif::_err_msgs.at("E200"));

  return std::make_pair(terms[0], terms[1]);
}

auto Blif::Parser::_createGateNand2(const Tokens& tokens)
  throw(IfExc) -> void {
  static const std::array<std::string, 2> inputs = {"A", "B"};
  static const std::string output = "O";

  if(tokens.size() != 5) throw IfExc(Blif::_err_msgs.at("E201"));

  std::unordered_map<std::string, std::string> io_map;
  for(auto i = 2; i < 5; i++) {
    io_map.insert(this->_parseGateParams(tokens[i]));
  }

  auto gate = std::make_unique<X>();
  for(const auto& input : inputs) {
    if(!io_map.count(input)) throw IfExc(Blif::_err_msgs.at("E201"));

    const auto& wire_name = io_map.at(input);
    this->_addBit(wire_name);
    gate->addCbit(Cbit(bit_map_.at(wire_name)));
  }
  {
    if(!io_map.count(output)) throw IfExc(Blif::_err_msgs.at("E201"));

    const auto& wire_name = io_map.at(output);
    this->_addBit(wire_name);
    gate->addTbit(Tbit(bit_map_.at(wire_name)));
  }

  const auto target_wire_name = io_map.at(output);
  const auto tbit_no = this->bit_map_.at(target_wire_name);

  if(this->_isAncilla(target_wire_name))  {
    // 使用する補助ビットが重複していないか
    if(this->middle_gate_map_.count(tbit_no)) {
      this->_warn("W200", target_wire_name);
    }
    this->middle_gate_map_[tbit_no] = std::move(gate);
  }
  else {
    this->output_gates_.push_back(std::move(gate));
  }
}

auto Blif::Parser::_createCircuit() -> Circuit {
  Circuit circuit;
  circuit.setDescription(this->model_name_);
  this->_placeGates(circuit);
  return circuit;
}

auto Blif::Parser::_placeGates(Circuit& circuit) -> void {
  std::queue<Bitno> queue;
  // 出力ゲートを配置
  for(const auto& gate : this->output_gates_) {
    for(const auto& tbit : gate->getCbitList()) {
      queue.push(tbit.bitno_);
    }
    circuit.addGate(gate->clone());
  }

  // 中間ゲートを配置
  while(!queue.empty()) {
    const auto bit_no = queue.front();
    queue.pop();

    if(!this->middle_gate_map_.count(bit_no)) continue;

    const auto gate = std::move(this->middle_gate_map_.at(bit_no));
    this->middle_gate_map_.erase(bit_no);
    for(const auto& tbit : gate->getCbitList()) {
      queue.push(tbit.bitno_);
    }
    circuit.addGate(gate->clone());
    circuit.insertGate(circuit.getGateListBegin(), gate->clone());
  }
}

auto Blif::Parser::parse()
  throw(IfExc, std::ios_base::failure) -> Circuit {
  std::ifstream ifs(this->filename_);

  if(ifs.fail()) throw std::ios_base::failure("Cannot open file.");

  this->_init();

  while(this->_parseLine(ifs));

  return this->_createCircuit();
}
}
}
