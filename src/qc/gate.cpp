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

/**
 * @fn Gate(const Tbit& tbit)
 * @brief constructor
 * @param [in] tbit target bit
 * @detail none control bit, one target bit quantum gate constructor
 */
Gate::Gate(const Tbit& tbit) : tbits_{tbit} {
}

/**
 * @fn Gate(const Tbit& tbit1, const Tbit& tbit2)
 * @brief constructor
 * @param [in] tbit1 control bit
 * @param [in] tbit2 target bit
 * @detail two target bit quantum gate constructor
 */
Gate::Gate(const Tbit& tbit1, const Tbit& tbit2) : tbits_{tbit1, tbit2} {
}

/**
 * @fn Gate(const Cbit& cbit, const Tbit& tbit)
 * @brief constructor
 * @param [in] cbit control bit
 * @param [in] tbit target bit
 * @detail one control bit, one target bit quantum gate constructor
 */
Gate::Gate(const Cbit& cbit, const Tbit& tbit) : cbits_{cbit}, tbits_{tbit} {
}

/**
 * @fn Gate(const Cbit& cbit, const TbitList& tbits)
 * @brief constructor
 * @param [in] cbit control bit
 * @param [in] tbits target bits
 * @detail one control bit, some target bits quantum gate constructor
 *         from the list tbits the gate is constructed
 */
Gate::Gate(const Cbit& cbit, const TbitList& tbits) :
  cbits_{cbit}, tbits_(tbits) {
}

/**
 * @fn Gate(const Cbit& cbit, const std::initializer_list<Tbit>& tbits)
 * @brief constructor
 * @param [in] cbit control bit
 * @param [in] tbits target bits
 * @detail one control bit, some target bits quantum gate constructor
 *         from the list tbits the gate is constructed
 */
Gate::Gate(const Cbit& cbit, const std::initializer_list<Tbit>& tbits) :
  cbits_{cbit}, tbits_(tbits) {
}

/**
 * @fn Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit)
 * @brief constructor
 * @param [in] cbit1 control bit
 * @param [in] cbit2 control bit
 * @param [in] tbit target bit
 * @detail two control bits, one target bit quantum gate constructor
 */
Gate::Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit) :
  cbits_{cbit1, cbit2}, tbits_{tbit} {
}

/**
 * @fn Gate(const CbitList& cbits, const Tbit& tbit)
 * @brief constructor
 * @param [in] cbits control bits
 * @param [in] tbit target bit
 * @detail some control bits, one target bit quantum gate constructor
 *         from the list cbits and one tbit the gate is constructed
 */
Gate::Gate(const CbitList& cbits, const Tbit& tbit) :
  cbits_(cbits), tbits_{tbit} {
}

/**
 * @fn Gate(const std::initializer_list<Cbit>& cbits, const Tbit& tbit)
 * @brief constructor
 * @param [in] cbits control bits
 * @param [in] tbit target bit
 * @detail some control bits, one target bit quantum gate constructor
 *         from the list cbits and one tbit the gate is constructed
 */
Gate::Gate(const std::initializer_list<Cbit>& cbits, const Tbit& tbit) :
  cbits_(cbits), tbits_{tbit} {
}

/**
 * @fn Gate(const CbitList& cbits, const TbitList& tbits)
 * @brief constructor
 * @param [in] cbits control bits
 * @param [in] tbits target bits
 * @detail some control bits, some target bits quantum gate constructor
 *         from the list cbits and tbits the gate is constructed
 */
Gate::Gate(const CbitList& cbits, const TbitList& tbits) :
  cbits_(cbits), tbits_(tbits) {
}

/**
 * @fn Gate(const std::initializer_list<Cbit>& cbits, \
 *          const std::initializer_list<Tbit>& tbits)
 * @brief constructor
 * @param [in] cbits control bits
 * @param [in] tbits target bits
 * @detail some control bits, some target bits quantum gate constructor
 *         from the list cbits and tbits the gate is constructed
 */
Gate::Gate(const std::initializer_list<Cbit>& cbits, \
           const std::initializer_list<Tbit>& tbits) :
  cbits_(cbits), tbits_(tbits) {
}

/**
 * @fn Gate(const Gate& other)
 * @brief copy constructor
 * @param [in] other another Gate class object
 */
Gate::Gate(const Gate& other): cbits_(other.cbits_), tbits_(other.tbits_) {
}

auto Gate::_getPositivePolarityMask() const -> ui {
  auto ordered_cbits = util::container::convert<std::set>(this->cbits_);
  ui result = 0;
  for(const auto& cbit : ordered_cbits) {
    result <<= 1;
    if(cbit.polarity_) result++;
  }
  return result;
}

auto Gate::_updatePositiveMatrixies(MatrixMap<Bitno>& matrixies, \
                                    bool is_cbit, bool is_positive, \
                                    Bitno bit) const -> void {
  using util::matrix::ketbra;

  auto c_matrix = is_positive ? ketbra<1>() : ketbra<0>();
  for(auto& matrix : matrixies) {
    Matrix tmp;
    if(bit == matrix.first) tmp = this->getTargetMatrix();
    else if(is_cbit)        tmp = c_matrix;
    else                    tmp = util::matrix::identity();
    matrix.second = util::matrix::tensor(matrix.second, tmp);
  }
}

auto Gate::_updateNegativeMatrixies(MatrixMap<ui>& matrixies, \
                                    bool is_cbit, ui mask) const -> void {
  using util::matrix::ketbra;

  for(auto& matrix : matrixies) {
    Matrix tmp;
    if(is_cbit) tmp = matrix.first & mask ? ketbra<1>() : ketbra<0>();
    else        tmp = util::matrix::identity();
    matrix.second = util::matrix::tensor(matrix.second, tmp);
  }
}

auto Gate::_computeMatrix(const MatrixMap<Bitno>& p_matrixies, \
                          const MatrixMap<ui>& n_matrixies) const
  -> Matrix {
  auto size = p_matrixies.begin()->second.rows();
  auto result = util::matrix::identity(size);
  for(const auto& p_matrix : p_matrixies) {
    auto matrix = p_matrix.second;
    for(const auto& n_matrix : n_matrixies) {
      matrix += n_matrix.second;
    }
    result = result * matrix;
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
 * @fn bool operator!=(const Gate& other) const
 * @brief nonequivalence operator
 * @param [in] other another Gate class object
 * @return true or false
 */
auto Gate::operator!=(const Gate& other) const -> bool {
  return !(*this == other);
}

auto Gate::computeMatrix(const std::set<Bitno>& bits) const -> Matrix {
  ui matrix_count = std::pow(2, this->cbits_.size());
  ui mask = 1 << (this->cbits_.size() - 1);
  auto positive = this->_getPositivePolarityMask();

  MatrixMap<Bitno> p_matrixies;
  for(const auto& tbit : this->tbits_) {
    p_matrixies[tbit.bitno_] = util::matrix::identity(1);
  }
  MatrixMap<ui> n_matrixies;
  for(ui i = 0; i < matrix_count; i++) {
    if(i != positive) n_matrixies[i] = util::matrix::identity(1);
  }

  for(const auto& bit : bits) {
    auto is_cbit = this->isIncludedInCbitList(bit);
    this->_updatePositiveMatrixies(p_matrixies, is_cbit, mask & positive, bit);
    this->_updateNegativeMatrixies(n_matrixies, is_cbit, mask);
    if(is_cbit) mask >>= 1;
  }

  return std::move(this->_computeMatrix(p_matrixies, n_matrixies));
}

/**
 * @fn BitList getUsedBits() const
 * @brief take used bits are control bits and target bits
 * @return used bits
 */
auto Gate::getUsedBits() const -> BitList {
  BitList used_bits;
  for(const auto& cbit : this->cbits_) {
    used_bits.insert(cbit.bitno_);
  }
  for(const auto& tbit : this->tbits_) {
    used_bits.insert(tbit.bitno_);
  }
  return std::move(used_bits);
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

auto Swap::decompose() const -> GateList {
  assert(static_cast<int>(this->tbits_.size()) == 2);

  auto tbits = util::container::convert<std::vector>(this->tbits_);
  std::vector<CbitList> cbit_lists(2, this->cbits_);
  cbit_lists[0].insert(Cbit(tbits[0].bitno_));
  cbit_lists[1].insert(Cbit(tbits[1].bitno_));

  GateList gates;
  gates.emplace_back(new Not(cbit_lists[0], tbits[1]));
  gates.emplace_back(new Not(cbit_lists[1], tbits[0]));
  gates.emplace_back(new Not(cbit_lists[0], tbits[1]));

  return std::move(gates);
}
}
