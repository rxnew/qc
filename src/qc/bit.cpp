/**
 * @file bit.cpp
 * @brief implementation of the control and target bit class
 */

#include "bit.hpp"

namespace qc {
Bit::Bit() : bitno_(0) {
}

/**
 * @fn Bit(Bitno bitno)
 * @brief constructor
 * @param [in] bitno bit number
 */
Bit::Bit(Bitno bitno) : bitno_(bitno) {
}

/**
 * @fn Bit(const Bit& other)
 * @brief copy constructor
 * @param [in] other another Bit class object
 */
Bit::Bit(const Bit& other) : bitno_(other.bitno_) {
}

Bit::~Bit() {
}

/**
 * @fn Cbit(Bitno bitno, bool polarity)
 * @brief constructor
 * @param [in] bitno bit number
 * @param [in] polarity polarity
 * @detail polarity is true for positive control, false for negative control
 */
Cbit::Cbit(Bitno bitno, bool polarity) : Bit(bitno), polarity_(polarity) {
}

/**
 * @fn Cbit(const Cbit& other)
 * @brief copy constructor
 * @param [in] other another Cbit class object
 */
Cbit::Cbit(const Cbit& other)
  : Bit(other.bitno_), polarity_(other.polarity_) {
}

/**
 * @fn Cbit& operator=(const Cbit& other)
 * @brief assignment operator
 * @param [in] other another Cbit class object
 * @return reference to this object
 */
auto Cbit::operator=(const Cbit& other) -> Cbit& {
  this->bitno_ = other.bitno_;
  this->polarity_ = other.polarity_;
  return *this;
}

/**
 * @fn bool operator<(const Cbit& other) const
 * @brief compare operator
 * @param [in] other another Cbit class object
 * @return true or false
 */
auto Cbit::operator<(const Cbit& other) const -> bool {
  if(this->bitno_ != other.bitno_) {
    return Bit::operator<(other);
  }
  return !this->polarity_;
}
}
