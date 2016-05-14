/**
 * @file gate_impl.hpp
 * @brief implementation header of quantum gate classes
 */

#pragma once

namespace qc {
inline auto Gate::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {};
}

inline Gate::Gate(const Tbit& tbit) : tbits_{tbit} {
}

inline Gate::Gate(const Tbit& tbit1, const Tbit& tbit2) : tbits_{tbit1, tbit2} {
}

inline Gate::Gate(const Cbit& cbit, const Tbit& tbit)
  : cbits_{cbit}, tbits_{tbit} {
}

inline Gate::Gate(const Cbit& cbit, const TbitList& tbits)
  : cbits_{cbit}, tbits_(tbits) {
}

inline Gate::Gate(const Cbit& cbit, TbitList&& tbits)
  : cbits_{cbit}, tbits_(std::move(tbits)) {
}

inline Gate::Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit)
  : cbits_{cbit1, cbit2}, tbits_{tbit} {
}

inline Gate::Gate(const CbitList& cbits, const Tbit& tbit) :
  cbits_(cbits), tbits_{tbit} {
}

inline Gate::Gate(CbitList&& cbits, const Tbit& tbit) :
  cbits_(std::move(cbits)), tbits_{tbit} {
}

inline Gate::Gate(const CbitList& cbits, const TbitList& tbits) :
  cbits_(cbits), tbits_(tbits) {
}

inline Gate::Gate(CbitList&& cbits, TbitList&& tbits) :
  cbits_(std::move(cbits)), tbits_(std::move(tbits)) {
}

inline auto Gate::operator!=(const Gate& other) const -> bool {
  return !(*this == other);
}

inline auto Gate::getCbitList() const -> const CbitList& {
  return this->cbits_;
}

inline auto Gate::getTbitList() const -> const TbitList& {
  return this->tbits_;
}

inline auto Gate::setCbits(const CbitList& cbits) -> void {
  this->cbits_ = cbits;
}

inline auto Gate::setCbits(CbitList&& cbits) -> void {
  this->cbits_ = std::move(cbits);
}

inline auto Gate::setTbits(const TbitList& tbits) -> void {
  this->tbits_ = tbits;
}

inline auto Gate::setTbits(TbitList&& tbits) -> void {
  this->tbits_ = std::move(tbits);
}

inline auto Gate::isIncluded(Bitno bit) const -> bool {
  return this->isIncludedInTbitList(bit) || this->isIncludedInCbitList(bit);
}

inline auto Gate::isIncludedInCbitList(Bitno bit) const -> bool {
  return
    this->cbits_.count(Cbit(bit, true)) ||
    this->cbits_.count(Cbit(bit, false));
}

inline auto Gate::isIncludedInTbitList(Bitno bit) const -> bool {
  return this->tbits_.count(Tbit(bit));
}

inline auto Gate::computeMatrix(const std::set<Bitno>& bits) const -> Matrix {
  return std::move(this->_computeMatrix(MatrixMap(*this, bits)));
}

inline auto Gate::computeMatrix(const BitList& bits) const -> Matrix {
  return this->computeMatrix(util::container::convert<std::set>(bits));
}

inline auto Gate::computeMatrix() const -> Matrix {
  return this->computeMatrix(this->collectUsedBits());
}

inline auto Gate::simulate(const Vector& input, const std::set<Bitno>& bits) \
  const -> Vector {
  assert(input.rows() == std::pow(2, bits.size()));
  return std::move(this->_simulate(input, MatrixMap(*this, bits)));
}

inline auto Gate::simulate(const Vector& input, const BitList& bits) const
  -> Vector {
  auto ordered_bits = util::container::convert<std::set>(bits);
  return this->simulate(input, ordered_bits);
}

inline auto Gate::simulate(const Vector& input) const -> Vector {
  return this->simulate(input, this->collectUsedBits());
}

inline auto Gate::isControlled() const -> bool {
  return !this->cbits_.empty();
}

inline auto Gate::isSingleControlled() const -> bool {
  return this->cbits_.size() == 1;
}

inline auto Gate::isMultiControlled() const -> bool {
  return this->cbits_.size() > 1;
}

inline auto Gate::isSingleTarget() const -> bool {
  return this->tbits_.size() == 1;
}

inline auto Gate::isMultiTarget() const -> bool {
  assert(!this->tbits_.empty());
  return !this->isSingleTarget();
}

inline auto Gate::isSingleQubitRotation() const -> bool {
  return !this->isControlled() && this->isSingleTarget();
}

inline auto Gate::MatrixMap::_mask(ui polarity_pattern) const -> bool {
  return polarity_pattern & polarity_pattern_mask_;
}

inline auto Gate::MatrixMap::_isActive() const -> bool {
  return this->_mask(this->active_polarity_pattern_);
}
}
