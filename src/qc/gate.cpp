/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "gate.hpp"

namespace qc {
#define DEF_GATE_MEMBER_VAR(type) \
  const std::string type::TYPE_NAME = #type; \
  const Matrix type::TARGET_MATRIX = \
    util::eigen::create(type::_createTargetMatrixList());

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

auto Gate::_getCbitMatrixies(const std::set<Bitno>& bits) const
  -> std::unordered_map<Bitno, Matrix> {
  using util::eigen::ketbra;
  using util::eigen::identity;

  std::unordered_map<Bitno, Matrix> matrixies;

  for(const auto& cbit : this->cbits_) {
    matrixies[cbit.bitno_] = identity(1);
  }

  for(const auto& bit : bits) {
    for(auto& matrix : matrixies) {
      auto tmp = bit == matrix.first ? ketbra<0>() : identity();
      matrix.second = util::eigen::tensor(matrix.second, tmp);
    }
  }

  return std::move(matrixies);
}

auto Gate::_getTbitMatrixies(const std::set<Bitno>& bits) const
  -> std::unordered_map<Bitno, Matrix> {
  using util::eigen::ketbra;
  using util::eigen::identity;

  std::unordered_map<Bitno, Matrix> matrixies;

  for(const auto& tbit : this->tbits_) {
    matrixies[tbit.bitno_] = identity(1);
  }

  for(const auto& bit : bits) {
    auto op = this->cbits_.count(Cbit(bit)) ? ketbra<1>() : identity();
    for(auto& matrix : matrixies) {
      auto tmp = bit == matrix.first ? this->getTargetMatrix() : op;
      matrix.second = util::eigen::tensor(matrix.second, tmp);
    }
  }

  return std::move(matrixies);
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

auto Gate::_getPositivePolarityMask() const -> int {
  auto ordered_cbits = util::container::convert<std::set>(this->cbits_);
  int result = 0;
  for(const auto& cbit : ordered_cbits) {
    result <<= 1;
    if(cbit.polarity_) result++;
  }
  return result;
}

auto Gate::getMatrix(const std::set<Bitno>& bits) const -> Matrix {
  using util::eigen::ketbra;
  using util::eigen::identity;
  using util::eigen::tensor;

  std::vector<Matrix> negative_matrixies(std::pow(2, this->cbits_.size()), identity(1));
  std::unordered_map<Bitno, Matrix> positive_matrixies;
  for(const auto& tbit : this->tbits_) {
    positive_matrixies[tbit.bitno_] = identity(1);
  }

  auto size = std::pow(2, bits.size());
  auto positive = this->_getPositivePolarityMask();
  int mask = 1 << (this->cbits_.size() - 1);

  for(const auto& bit : bits) {
    bool cbit_flg = this->isIncludedInCbit(bit);

    for(auto& matrix : positive_matrixies) {
      Matrix tmp;
      if(bit == matrix.first) {
        tmp = this->getTargetMatrix();
      }
      else if(cbit_flg) {
        tmp = positive & mask ? ketbra<1>() : ketbra<0>();
      }
      else {
        tmp = identity();
      }
      matrix.second = tensor(matrix.second, tmp);
    }

    for(int i = 0; i < static_cast<int>(negative_matrixies.size()); i++) {
      if(i == positive) continue;
      Matrix tmp;
      if(cbit_flg) {
        tmp = i & mask ? ketbra<1>() : ketbra<0>();
      }
      else {
        tmp = identity();
      }
      negative_matrixies[i] = tensor(negative_matrixies[i], tmp);
    }

    if(cbit_flg) mask >>= 1;
  }

  auto result = identity(size);
  for(const auto& positive_matrix : positive_matrixies) {
    auto matrix = positive_matrix.second;
    for(int i = 0; i < static_cast<int>(negative_matrixies.size()); i++) {
      if(i == positive) continue;
      matrix += negative_matrixies[i];
    }
    result = result * matrix;
  }

  return std::move(result);
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

auto Swap::getMatrix(const std::set<Bitno>& bits) const -> Matrix {
  auto gates = this->decompose();
  auto size = static_cast<size_t>(std::pow(2, bits.size()));
  auto result = util::eigen::identity(size);
  for(const auto& gate : gates) {
    result = gate->getMatrix(bits) * result;
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
