/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "gate.hpp"

namespace qc {
/**
 * @fn Gate(const Tbit& tbit)
 * @brief constructor
 * @param [in] tbit target bit
 * @detail none control bit, one target bit quantum gate constructor
 */
Gate::Gate(const Tbit& tbit) {
  this->tbits_.insert(tbit);
}

/**
 * @fn Gate(const TbitList& tbits)
 * @brief constructor
 * @param [in] tbits target bits
 * @detail none control bit, some target bits quantum gate constructor
 *         from the list tbits the gate is constructed
 */
Gate::Gate(const TbitList& tbits) : tbits_(tbits) {
}

/**
 * @fn Gate(const Cbit& cbit, const Tbit& tbit)
 * @brief constructor
 * @param [in] cbit control bit
 * @param [in] tbit target bit
 * @detail one control bit, one target bit quantum gate constructor
 */
Gate::Gate(const Cbit& cbit, const Tbit& tbit) {
  this->cbits_.insert(cbit);
  this->tbits_.insert(tbit);
}

/**
 * @fn Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit)
 * @brief constructor
 * @param [in] cbit1 control bit
 * @param [in] cbit2 control bit
 * @param [in] tbit target bit
 * @detail two control bits, one target bit quantum gate constructor
 */
Gate::Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit) {
  this->cbits_.insert(cbit1);
  this->cbits_.insert(cbit2);
  this->tbits_.insert(tbit);
}

/**
 * @fn Gate(const CbitList& cbits, const Tbit& tbit)
 * @brief constructor
 * @param [in] cbits control bits
 * @param [in] tbit target bit
 * @detail some control bits, one target bit quantum gate constructor
 *         from the list cbits and one tbit the gate is constructed
 */
Gate::Gate(const CbitList& cbits, const Tbit& tbit) : cbits_(cbits) {
  this->tbits_.insert(tbit);
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
 * @fn Gate(const Gate& other)
 * @brief copy constructor
 * @param [in] other another Gate class object
 */
Gate::Gate(const Gate& other): cbits_(other.cbits_), tbits_(other.tbits_) {
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
Gate& Gate::operator=(const Gate& other) {
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
bool Gate::operator==(const Gate& other) const {
  if(this->getGateType() != other.getGateType()) return false;
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
bool Gate::operator!=(const Gate& other) const {
  return !(*this == other);
}

/**
 * @fn BitList getUsedBits() const
 * @brief take used bits are control bits and target bits
 * @return used bits
 */
BitList Gate::getUsedBits() const {
  BitList used_bits;
  for(const auto& cbit : this->cbits_)
    used_bits.insert(cbit.bitno_);
  for(const auto& tbit : this->tbits_)
    used_bits.insert(tbit.bitno_);
  return std::move(used_bits);
}

/**
 * @fn bool isAllPositive() const
 * @brief check whether all bits are positive
 * @return true or false
 */
bool Gate::isAllPositive() const {
  for(const auto& cbit : this->cbits_)
    if(!cbit.polarity_) return false;
  return true;
}

/**
 * @fn virtual void print(std::ostream& os) const
 * @brief print this gate
 * @param [in] os output stream object
 */
void Gate::print(std::ostream& os) const {
  auto ordered_cbits = util::getOrderedContainer(this->cbits_);
  auto ordered_tbits = util::getOrderedContainer(this->tbits_);

  os << "\\ ";
  for(const auto& cbit : ordered_cbits)
    os << cbit << " ";
  for(const auto& tbit : ordered_tbits)
    os << tbit << " ";
}

V::V(const Tbit& tbit) : Gate(tbit) {
}

V::V(const TbitList& tbits) : Gate(tbits) {
}

V::V(const Cbit& cbit, const Tbit& tbit) : Gate(cbit, tbit) {
}

V::V(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit) :
  Gate(cbit1, cbit2, tbit) {
}

V::V(const CbitList& cbits, const Tbit& tbit) : Gate(cbits, tbit) {
}

V::V(const CbitList& cbits, const TbitList& tbits) : Gate(cbits, tbits) {
}

void V::print(std::ostream& os) const {
  os << "V ";
  Gate::print(os);
  os << "\\ \\ " << std::endl;
}

VPlus::VPlus(const Tbit& tbit) : Gate(tbit) {
}

VPlus::VPlus(const TbitList& tbits) : Gate(tbits) {
}

VPlus::VPlus(const Cbit& cbit, const Tbit& tbit) : Gate(cbit, tbit) {
}

VPlus::VPlus(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit) :
  Gate(cbit1, cbit2, tbit) {
}

VPlus::VPlus(const CbitList& cbits, const Tbit& tbit) : Gate(cbits, tbit) {
}

VPlus::VPlus(const CbitList& cbits, const TbitList& tbits) :
  Gate(cbits, tbits) {
}

void VPlus::print(std::ostream& os) const {
  os << "VPlus ";
  Gate::print(os);
  os << "\\ \\ " << std::endl;
}

H::H(const Tbit& tbit) : Gate(tbit) {
}

H::H(const TbitList& tbits) : Gate(tbits) {
}

H::H(const Cbit& cbit, const Tbit& tbit) : Gate(cbit, tbit) {
}

H::H(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit) :
  Gate(cbit1, cbit2, tbit) {
}

H::H(const CbitList& cbits, const Tbit& tbit) : Gate(cbits, tbit) {
}

H::H(const CbitList& cbits, const TbitList& tbits) : Gate(cbits, tbits) {
}

void H::print(std::ostream& os) const {
  os << "H ";
  Gate::print(os);
  os << "\\ \\ " << std::endl;
}

Not::Not(const Tbit& tbit) : Gate(tbit) {
}

Not::Not(const TbitList& tbits) : Gate(tbits) {
}

Not::Not(const Cbit& cbit, const Tbit& tbit) : Gate(cbit, tbit) {
}

Not::Not(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit) :
  Gate(cbit1, cbit2, tbit) {
}

Not::Not(const CbitList& cbits, const Tbit& tbit) : Gate(cbits, tbit) {
}

Not::Not(const CbitList& cbits, const TbitList& tbits) : Gate(cbits, tbits) {
}

void Not::print(std::ostream& os) const {
  os << "Not ";
  Gate::print(os);
  os << "\\ \\ " << std::endl;
}

Z::Z(const Tbit& tbit) : Gate(tbit) {
}

Z::Z(const TbitList& tbits) : Gate(tbits) {
}

Z::Z(const Cbit& cbit, const Tbit& tbit) : Gate(cbit, tbit) {
}

Z::Z(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit) :
  Gate(cbit1, cbit2, tbit) {
}

Z::Z(const CbitList& cbits, const Tbit& tbit) : Gate(cbits, tbit) {
}

Z::Z(const CbitList& cbits, const TbitList& tbits) : Gate(cbits, tbits) {
}

void Z::print(std::ostream& os) const {
  os << "Z ";
  Gate::print(os);
  os << "\\ \\ " << std::endl;
}
}
