/**
 * @file bit.cpp
 * @brief implementation of the control and target bit class
 */

#include "bit.hpp"

namespace qc {
Cbit::Cbit() : bitno_(0) {
}

/**
 * @fn Cbit(Bitno bitno)
 * @brief constructor
 * @param [in] bitno bit number
 * @detail polarity is positive
 */
Cbit::Cbit(Bitno bitno) : bitno_(bitno), polarity_(true) {
}

/**
 * @fn Cbit(Bitno bitno, bool polarity)
 * @brief constructor
 * @param [in] bitno bit number
 * @param [in] polarity polarity
 * @detail polarity is true for positive control, false for negative control
 */
Cbit::Cbit(Bitno bitno, bool polarity) : bitno_(bitno), polarity_(polarity) {
}

/**
 * @fn Cbit(const Cbit& other)
 * @brief copy constructor
 * @param [in] other another Cbit class object
 */
Cbit::Cbit(const Cbit& other)
  : bitno_(other.bitno_), polarity_(other.polarity_) {
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
    return this->bitno_ < other.bitno_;
  }
  return !this->polarity_;
}

Tbit::Tbit() : bitno_(0) {
}

/**
 * @fn Tbit(Bitno bitno)
 * @brief constructor
 * @param [in] bitno bit number
 */
Tbit::Tbit(Bitno bitno) : bitno_(bitno) {
}

/**
 * @fn Tbit(const Tbit& other)
 * @brief copy constructor
 * @param [in] other another Tbit class object
 */
Tbit::Tbit(const Tbit& other) : bitno_(other.bitno_) {
}
}
