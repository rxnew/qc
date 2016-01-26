/**
 * @file gate.cpp
 * @brief implementation of quantum gate classes
 */

#include "gate.hpp"

namespace qc {
#define DEF_TYPE_NAME(type) const std::string type::TYPE_NAME = #type

DEF_TYPE_NAME(Gate);
DEF_TYPE_NAME(V);
DEF_TYPE_NAME(VPlus);
DEF_TYPE_NAME(Hadamard);
DEF_TYPE_NAME(Not);
DEF_TYPE_NAME(Z);
DEF_TYPE_NAME(Swap);
DEF_TYPE_NAME(T);

#undef DEF_TYPE_NAME

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
  auto ordered_cbits = util::ContainerHelper::convert<std::set>(this->cbits_);
  auto ordered_tbits = util::ContainerHelper::convert<std::set>(this->tbits_);

  os << this->getTypeName() << ' ';
  os << R"(\ )";
  for(const auto& cbit : ordered_cbits) {
    os << cbit << ' ';
  }
  for(const auto& tbit : ordered_tbits) {
    os << tbit << ' ';
  }
  os << R"(\\)" << std::endl;
}
}
