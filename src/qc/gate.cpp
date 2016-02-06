/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "gate.hpp"

namespace qc {
#define DEF_GATE_MEMBER_VAR(type) \
  const std::string type::TYPE_NAME = #type; \
  const Matrix type::TARGET_MATRIX = \
    util::matrix::create(type::_createTargetMatrixList());

DEF_GATE_MEMBER_VAR(Gate);
DEF_GATE_MEMBER_VAR(V);
DEF_GATE_MEMBER_VAR(VPlus);
DEF_GATE_MEMBER_VAR(Hadamard);
DEF_GATE_MEMBER_VAR(Not);
DEF_GATE_MEMBER_VAR(Z);
DEF_GATE_MEMBER_VAR(Swap);
DEF_GATE_MEMBER_VAR(T);

#undef DEF_GATE_MEMBER_VAR

auto Gate::_computeActivePolarityPattern() const -> ui {
  auto ordered_cbits = util::container::convert<std::set>(this->cbits_);
  ui result = 0;
  for(const auto& cbit : ordered_cbits) {
    result <<= 1;
    if(cbit.polarity_) result++;
  }
  return result;
}

auto Gate::_updateActiveMatrixMap(MatrixMap<Bitno>& matrix_map, \
                                  bool is_cbit, bool is_active, \
                                  Bitno bit) const -> void {
  using util::matrix::ketbra;

  auto c_matrix = is_active ? ketbra<1>() : ketbra<0>();
  for(auto& matrix : matrix_map) {
    Matrix tmp;
    if(bit == matrix.first) tmp = this->getTargetMatrix();
    else if(is_cbit)        tmp = c_matrix;
    else                    tmp = util::matrix::identity();
    matrix.second = util::matrix::tensor(matrix.second, tmp);
  }
}

auto Gate::_updateInactiveMatrixMap(MatrixMap<ui>& matrix_map, \
                                    bool is_cbit, ui mask) const -> void {
  using util::matrix::ketbra;

  for(auto& matrix : matrix_map) {
    Matrix tmp;
    if(is_cbit) tmp = matrix.first & mask ? ketbra<1>() : ketbra<0>();
    else        tmp = util::matrix::identity();
    matrix.second = util::matrix::tensor(matrix.second, tmp);
  }
}

auto Gate::_computeMatrixMap(const std::set<Bitno>& bits) const
  -> std::tuple<MatrixMap<Bitno>, MatrixMap<ui>> {
  ui matrix_count = std::pow(2, this->cbits_.size());
  ui mask = 1 << (this->cbits_.size() - 1);
  auto active_pattern = this->_computeActivePolarityPattern();

  // each target
  MatrixMap<Bitno> active_matrix_map;
  for(const auto& tbit : this->tbits_) {
    active_matrix_map[tbit.bitno_] = util::matrix::identity(1);
  }
  // each input pattern
  MatrixMap<ui> inactive_matrix_map;
  for(ui i = 0; i < matrix_count; i++) {
    if(i != active_pattern) inactive_matrix_map[i] = util::matrix::identity(1);
  }

  for(const auto& bit : bits) {
    auto is_cbit = this->isIncludedInCbitList(bit);
    auto is_active = mask & active_pattern;
    this->_updateActiveMatrixMap(active_matrix_map, is_cbit, is_active, bit);
    this->_updateInactiveMatrixMap(inactive_matrix_map, is_cbit, mask);
    if(is_cbit) mask >>= 1;
  }

  return std::move(std::make_tuple(active_matrix_map, inactive_matrix_map));
}

auto Gate::_computeMatrix(const MatrixMap<Bitno>& active_matrix_map, \
                          const MatrixMap<ui>& inactive_matrix_map) const
  -> Matrix {
  assert(!active_matrix_map.empty());

  auto size = active_matrix_map.begin()->second.rows();
  auto result = util::matrix::identity(size);
  for(const auto& active_matrix : active_matrix_map) {
    auto matrix = active_matrix.second;
    for(const auto& inactive_matrix : inactive_matrix_map) {
      matrix += inactive_matrix.second;
    }
    result = matrix * result;
  }
  return std::move(result);
}

auto Gate::_simulate(const Vector& input, \
                     const MatrixMap<Bitno>& active_matrix_map, \
                     const MatrixMap<ui>& inactive_matrix_map) const -> Vector {
  assert(!active_matrix_map.empty());

  auto result = input;
  for(const auto& active_matrix : active_matrix_map) {
    auto matrix = active_matrix.second;
    for(const auto& inactive_matrix : inactive_matrix_map) {
      matrix += inactive_matrix.second;
    }
    result = matrix * result;
  }
  return std::move(result);
}

/**
 * @fn virtual ~Gate()
 * @brief virtual destructor
 */
Gate::~Gate() {
  this->cbits_.clear();
  this->tbits_.clear();
}

/**
 * @fn Gate& operator=(const Gate& other)
 * @brief assignment operator
 * @param [in] other another Gate class object
 * @return reference to this object
 */
auto Gate::operator=(const Gate& other) -> Gate& {
  this->cbits_ = other.cbits_;
  this->tbits_ = other.tbits_;
  return *this;
}

/**
 * @fn bool operator==(const Gate& other) const
 * @brief equality operator
 * @param [in] other another Gate class object
 * @return true or false
 */
auto Gate::operator==(const Gate& other) const -> bool {
  if(this->getTypeName() != other.getTypeName()) return false;
  if(this->cbits_ != other.cbits_) return false;
  if(this->tbits_ != other.tbits_) return false;
  return true;
}

/**
 * @fn BitList collectUsedBits() const
 * @brief take used bits are control bits and target bits
 * @return used bits
 */
auto Gate::collectUsedBits() const -> BitList {
  BitList used_bits;
  for(const auto& cbit : this->cbits_) {
    used_bits.insert(cbit.bitno_);
  }
  for(const auto& tbit : this->tbits_) {
    used_bits.insert(tbit.bitno_);
  }
  return std::move(used_bits);
}

auto Gate::computeMatrix(const std::set<Bitno>& bits) const -> Matrix {
  auto matrix_maps = this->_computeMatrixMap(bits);
  auto active_matrix_map = std::get<0>(matrix_maps);
  auto inactive_matrix_map = std::get<1>(matrix_maps);
  return \
    std::move(this->_computeMatrix(active_matrix_map, inactive_matrix_map));
}

auto Gate::simulate(const Vector& input, const std::set<Bitno>& bits) const
  -> Vector {
  assert(input.rows() == std::pow(2, bits.size()));

  auto matrix_maps = this->_computeMatrixMap(bits);
  auto active_matrix_map = std::get<0>(matrix_maps);
  auto inactive_matrix_map = std::get<1>(matrix_maps);
  return \
    std::move(this->_simulate(input, active_matrix_map, inactive_matrix_map));
}

/**
 * @fn bool isAllPositive() const
 * @brief check whether all bits are positive
 * @return true or false
 */
auto Gate::isAllPositive() const -> bool {
  for(const auto& cbit : this->cbits_) {
    if(!cbit.polarity_) return false;
  }
  return true;
}

/**
 * @fn virtual void print(std::ostream& os) const
 * @brief print this gate
 * @param [in] os output stream object
 */
auto Gate::print(std::ostream& os) const -> void {
  auto ordered_cbits = util::container::convert<std::set>(this->cbits_);
  auto ordered_tbits = util::container::convert<std::set>(this->tbits_);

  os << this->getTypeName() << ' ';
  os << R"(\ )";
  for(const auto& cbit : ordered_cbits) {
    os << cbit << ' ';
  }
  for(const auto& tbit : ordered_tbits) {
    os << tbit << ' ';
  }
  os << R"(\ )";
  //os << this->getVariable() << ' ';
  os << R"(\ )";
  //os << this->getFunction();
  os << std::endl;
}

auto Swap::computeMatrix(const std::set<Bitno>& bits) const -> Matrix {
  auto gates = this->decompose();
  auto size = static_cast<size_t>(std::pow(2, bits.size()));
  auto result = util::matrix::identity(size);
  for(const auto& gate : gates) {
    result = gate->computeMatrix(bits) * result;
  }
  return std::move(result);
}

auto Swap::decompose() const -> std::list<GatePtr> {
  assert(static_cast<int>(this->tbits_.size()) == 2);

  auto tbits = util::container::convert<std::vector>(this->tbits_);
  std::vector<CbitList> cbit_lists(2, this->cbits_);
  cbit_lists[0].insert(Cbit(tbits[0].bitno_));
  cbit_lists[1].insert(Cbit(tbits[1].bitno_));

  std::list<GatePtr> gates;
  gates.emplace_back(new Not(cbit_lists[0], tbits[1]));
  gates.emplace_back(new Not(cbit_lists[1], tbits[0]));
  gates.emplace_back(new Not(cbit_lists[0], tbits[1]));

  return std::move(gates);
}
}
