/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "../gate.hpp"

namespace qc {
auto Gate::_computeMatrix(const MatrixMap& matrix_map) const -> Matrix {
  assert(!matrix_map.active_.empty());

  auto size = matrix_map.active_.begin()->second.rows();
  auto result = util::matrix::identity(size);
  for(const auto& active_matrix : matrix_map.active_) {
    auto matrix = active_matrix.second;
    for(const auto& inactive_matrix : matrix_map.inactive_) {
      matrix += inactive_matrix.second;
    }
    result = matrix * result;
  }
  return std::move(result);
}

auto Gate::_simulate(const Vector& input, const MatrixMap& matrix_map) const
  -> Vector {
  assert(!matrix_map.active_.empty());

  auto result = input;
  for(const auto& active_matrix : matrix_map.active_) {
    auto matrix = active_matrix.second;
    for(const auto& inactive_matrix : matrix_map.inactive_) {
      matrix += inactive_matrix.second;
    }
    result = matrix * result;
  }
  return std::move(result);
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

auto Gate::getCbit(Bitno bit) const -> const Cbit& {
  auto cbit_pos = this->cbits_.find(Cbit(bit, true));
  if(cbit_pos == this->cbits_.cend()) {
    cbit_pos = this->cbits_.find(Cbit(bit, false));
  }
  assert(cbit_pos != this->cbits_.cend());
  return *cbit_pos;
}

auto Gate::getTbit(Bitno bit) const -> const Tbit& {
  const auto tbit_pos = this->tbits_.find(Tbit(bit));
  assert(tbit_pos != this->tbits_.cend());
  return *tbit_pos;
}

auto Gate::invertCbitPolarity(Bitno bit) -> bool {
  auto polarity = this->getCbitPolarity(bit);
  this->cbits_.erase(Cbit(bit, polarity));
  this->addCbit(bit, polarity ^= true);
  return polarity;
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

  os << this->getTypeName();
  os << R"( \)";
  for(const auto& cbit : ordered_cbits) {
    os << ' ' << cbit;
  }
  for(const auto& tbit : ordered_tbits) {
    os << ' ' << tbit;
  }
  os << R"( \)";
  //os << ' ' << this->getVariable();
  os << R"( \)";
  //os << ' ' << this->getFunction();
  os << std::endl;
}

auto Gate::MatrixMap::_init() -> void {
  this->_setActivePolarityPattern();

  ui matrix_count = std::pow(2, this->gate_.cbits_.size());

  for(const auto& tbit : this->gate_.tbits_) {
    this->active_[tbit.bitno_] = util::matrix::identity(1);
  }
  for(ui i = 0; i < matrix_count; i++) {
    if(i == this->active_polarity_pattern_) continue;
    this->inactive_[i] = util::matrix::identity(1);
  }
}

auto Gate::MatrixMap::_setActivePolarityPattern() -> void {
  auto ordered_cbits = util::container::convert<std::set>(this->gate_.cbits_);
  this->active_polarity_pattern_ = 0;
  for(const auto& cbit : ordered_cbits) {
    this->active_polarity_pattern_ <<= 1;
    if(cbit.polarity_) this->active_polarity_pattern_++;
  }
}

auto Gate::MatrixMap::_updateActive(bool is_cbit, Bitno bit) -> void {
  using util::matrix::ketbra;

  auto c_matrix = this->_isActive() ? ketbra<1>() : ketbra<0>();
  for(auto& matrix : this->active_) {
    Matrix tmp;
    if(bit == matrix.first) tmp = this->gate_.getTargetMatrix();
    else if(is_cbit)        tmp = c_matrix;
    else                    tmp = util::matrix::identity();
    matrix.second = util::matrix::tensor(matrix.second, tmp);
  }
}

auto Gate::MatrixMap::_updateInactive(bool is_cbit) -> void {
  using util::matrix::ketbra;

  for(auto& matrix : this->inactive_) {
    Matrix tmp;
    if(is_cbit) tmp = this->_mask(matrix.first) ? ketbra<1>() : ketbra<0>();
    else        tmp = util::matrix::identity();
    matrix.second = util::matrix::tensor(matrix.second, tmp);
  }
}

Gate::MatrixMap::MatrixMap(const Gate& gate, const std::set<Bitno>& bits)
  : gate_(gate) {
  this->_init();
  this->polarity_pattern_mask_ = 1 << (this->gate_.cbits_.size() - 1);
  for(const auto& bit : bits) {
    auto is_cbit = gate.isIncludedInCbitList(bit);
    this->_updateActive(is_cbit, bit);
    this->_updateInactive(is_cbit);
    if(is_cbit) this->polarity_pattern_mask_ >>= 1;
  }
}
}
