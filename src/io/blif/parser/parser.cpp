#include "../parser.hpp"

#include <queue>

#include "../../../circuit.hpp"
#include "../../../gate/library/x.hpp"

namespace qc {
namespace io {
auto Blif::Parser::parse()
  throw(IfExc, std::ios_base::failure) -> Circuit {
  ifs_.open(filename_);

  if(ifs_.fail()) throw std::ios_base::failure("Cannot open file.");

  _init();

  while(_parse_line());

  ifs_.close();

  return _create_circuit();
}

auto Blif::Parser::_init() -> void {
  model_name_ = util::string::exclude_extension(filename_);
  input_wire_names_.clear();
  output_wire_names_.clear();
  lines_counter_ = 0;
  bit_map_.clear();
  bit_counter_ = 0;
  middle_gate_map_.clear();
}

auto Blif::Parser::_set_tokens(Tokens& tokens) -> void {
  std::getline(ifs_, line_);
  lines_counter_++;
  line_ = util::string::trim_comments(line_, '#');
  auto tokens_tmp = util::string::split(line_);
  tokens.insert(std::cend(tokens),
                std::make_move_iterator(std::begin(tokens_tmp)),
                std::make_move_iterator(std::end(tokens_tmp)));
}

auto Blif::Parser::_parse_line()
  throw(IfExc) -> bool {
  auto tokens = Tokens();
  _set_tokens(tokens);

  // 空行 or コメント行
  if(tokens.empty()) return true;
  if(tokens[0] == ".end") return false;

  // '\' による改行に対応
  while(tokens.back() == R"(\)") {
    tokens.pop_back();
    _set_tokens(tokens);
  }

  if(tokens[0] == ".model")        _parse_model_name(tokens);
  else if(tokens[0] == ".inputs")  _parse_inputs(tokens);
  else if(tokens[0] == ".outputs") _parse_outputs(tokens);
  else if(tokens[0] == ".clock")   _parse_clocks(tokens);
  else if(tokens[0] == ".gate")    _parse_gate(tokens);
  else if(tokens[0] == ".mlatch")  _parse_mlatch(tokens);
  else if(tokens[0] == ".latch")   _parse_latch(tokens);
  else if(tokens[0] == ".names")   _parse_names(tokens);
  else _error("E000");

  return true;
}

auto Blif::Parser::_parse_model_name(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "model";

  if(tokens.size() < 2u) _error("E010", name);

  model_name_ = tokens[1];
}

auto Blif::Parser::_parse_inputs(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "inputs";

  if(tokens.size() < 2u) _error("E010", name);

  for(auto i = 1u; i < tokens.size(); i++) {
    input_wire_names_.insert(tokens[i]);
    bit_map_[tokens[i]] = bit_counter_++;
  }
}

auto Blif::Parser::_parse_outputs(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "outputs";

  if(tokens.size() < 2u) _error("E010", name);

  for(auto i = 1u; i < tokens.size(); i++) {
    output_wire_names_.insert(tokens[i]);
    bit_map_[tokens[i]] = bit_counter_++;
  }
}

auto Blif::Parser::_parse_clocks(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "clock";

  if(tokens.size() < 2u) _error("E010", name);

  _warn("W000", name);
}

auto Blif::Parser::_parse_gate(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "gate";

  if(tokens.size() < 4u) _error("E010", name);

  auto const gate_name = tokens[1];
  if(gate_name == "nand2") _create_gate_nand2(tokens);
  else _warn("W010", gate_name);
}

auto Blif::Parser::_parse_mlatch(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "mlatch";

  if(tokens.size() < 2u) _error("E010", name);

  _warn("W000", name);
}

auto Blif::Parser::_parse_latch(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "latch";

  if(tokens.size() < 2u) _error("E010", name);

  _warn("W000", name);
}

auto Blif::Parser::_parse_names(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "names";

  if(tokens.size() < 2u) _error("E010", name);

  _warn("W000", name);

  auto pos = ifs_.tellg();
  while(std::getline(ifs_, line_)) {
    lines_counter_++;
    line_ = util::string::trim_white_spaces(line_);
    if(!line_.empty() && line_.front() == '.') {
      ifs_.seekg(pos);
      break;
    }
    pos = ifs_.tellg();
  }
}

auto Blif::Parser::_parse_subckt(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const name = "subckt";

  if(tokens.size() < 2u) _error("E010", name);

  _warn("W000", name);
}

auto Blif::Parser::_parse_gate_params(std::string const& token)
  throw(IfExc) ->  std::pair<std::string, std::string> {
  auto const terms = util::string::split(token, '=');

  if(terms.size() != 2u) _error("E020");

  return std::make_pair(terms[0], terms[1]);
}

auto Blif::Parser::_create_gate_nand2(Tokens const& tokens)
  throw(IfExc) -> void {
  static constexpr auto const inputs =
    std::array<char const* const, 2>{"A", "B"};
  static constexpr auto const output = "O";

  if(tokens.size() != 5u) _error("E021");

  auto io_map = std::unordered_map<std::string, std::string>();
  for(auto i = 2; i < 5; i++) {
    io_map.insert(_parse_gate_params(tokens[i]));
  }

  auto gate = Gate::make<X>();
  for(auto const& input : inputs) {
    if(!io_map.count(input)) _error("E021");

    auto const& wire_name = io_map.at(input);
    _add_bit(wire_name);
    gate.add_cbit(CBit(bit_map_.at(wire_name)));
  }
  {
    if(!io_map.count(output)) _error("E021");

    auto const& wire_name = io_map.at(output);
    _add_bit(wire_name);
    gate.add_tbit(TBit(bit_map_.at(wire_name)));
  }

  auto const target_wire_name = io_map.at(output);
  auto const tbit_no = bit_map_.at(target_wire_name);

  if(_is_ancilla(target_wire_name))  {
    // 使用する補助ビットが重複していないか
    if(middle_gate_map_.count(tbit_no)) {
      _warn("W020", target_wire_name);
    }
    middle_gate_map_.emplace(tbit_no, std::move(gate));
  }
  else {
    output_gates_.push_back(std::move(gate));
  }
}

auto Blif::Parser::_create_circuit() -> Circuit {
  auto circuit = Circuit();
  circuit.set_description(model_name_);
  _place_gates(circuit);
  return circuit;
}

auto Blif::Parser::_place_gates(Circuit& circuit) -> void {
  auto queue = std::queue<BitNo>();
  // 出力ゲートを配置
  for(auto const& gate : output_gates_) {
    for(auto const& tbit : gate.get_cbits()) {
      queue.push(tbit.get_no());
    }
    circuit.add_gate(gate);
  }

  // 中間ゲートを配置
  while(!queue.empty()) {
    auto const bit_no = queue.front();
    queue.pop();

    if(!middle_gate_map_.count(bit_no)) continue;

    auto const gate = std::move(middle_gate_map_.at(bit_no));
    middle_gate_map_.erase(bit_no);
    for(auto const& tbit : gate.get_cbits()) {
      queue.push(tbit.get_no());
    }
    circuit.add_gate(gate);
    circuit.insert_gate(circuit.begin_gates(), gate);
  }
}
}
}
