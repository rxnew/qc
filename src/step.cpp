/**
 * @file step.cpp
 * @brief implementation of the calculation step class
 */

#include "step.hpp"

namespace qc {
/**
 * @fn Step()
 * @brief constructor
 * @detail empty Step class constructor
 */
Step::Step() {
}

/**
 * @fn Step(const GatePtr& gate)
 * @brief constructor
 * @param [in] gate pointer to the quantum gate
 * @detail included one quantum gate Step class constructor
 */
Step::Step(const GatePtr& gate) {
  this->addGate(gate);
}

/**
 * @fn Step(Gate*&& gate)
 * @brief constructor
 * @param [in] gate pointer to the quantum gate
 * @detail included one quantum gate Step class constructor
 */
Step::Step(Gate*&& gate) {
  this->addGate(std::move(gate));
}

/**
 * @fn Step(const GateList& gates)
 * @brief constructor
 * @param [in] gates reference to the list of included quantum gates
 * @detail included some quantum gates Step class constructor
 */
Step::Step(const GateList& gates): gates_(gates) {
}

/**
 * @fn Step(const Step& other)
 * @brief copy constructor
 * @param [in] other another Step class object
 */
Step::Step(const Step& other) {
  for(const auto& gate : other.gates_)
    this->addGate(gate->clone());
}

/**
 * @fn ~Step()
 * @brief destructor
 */
Step::~Step() {
  this->gates_.clear();
}

/**
 * @fn Step& operator=(const Step& other)
 * @brief assignment operator
 * @param [in] other another Step class object
 * @return reference to this object
 */
Step& Step::operator=(const Step& other) {
  for(const auto& gate : this->gates_)
    this->addGate(gate->clone());
  return *this;
}

/**
 * @fn bool operator==(const Step& other) const
 * @brief equality operator
 * @param [in] other another Step class object
 * @return true or false
 */
bool Step::operator==(const Step& other) const {
  if(this->gates_.size() != other.gates_.size()) return false;
  for(const auto& gate : other.gates_)
    if(this->gates_.cend() == this->findSameGate(gate))
      return false;
  return true;
}

/**
 * @fn bool operator!=(const Step& other) const
 * @brief nonequivalence operator
 * @param [in] other another Step class object
 * @return true or false
 */
bool Step::operator!=(const Step& other) const {
  return !(*this == other);
}

CIterGateList Step::findSameGate(const GatePtr& gate) const {
  auto comp = [&gate](const GatePtr& obj) {return *gate == *obj;};
  return std::find_if(this->gates_.cbegin(), this->gates_.cend(), comp);
}

/**
 * @fn BitList getUsedBits() const
 * @brief take used bits of all included quanutm gates
 * @return used bits
 */
BitList Step::getUsedBits() const {
  BitList used_bits;
  for(const auto& gate : this->gates_) {
    auto gate_used_bits = gate->getUsedBits();
    used_bits.insert(gate_used_bits.cbegin(), gate_used_bits.cend());
  }
  return std::move(used_bits);
}

/**
 * @fn void calcDDMF(DDMFMgr& ddmf_mgr)
 * @brief calculate DDMF
 * @param [in] ddmf_mgr DDMF manager class object
 */
void Step::calcDDMF(DDMFMgr& ddmf_mgr) {
  DDMF ddmf_one(ddmf_mgr);
  DDMF ddmf_not = Matrix(Matrix::TYPE_N) * ddmf_one;

  for(const auto& gate : this->gates_) {
    const auto& cbits = gate->getCbitList();
    DDMF control_logic = ddmf_not;
    for(const auto& cbit : cbits) {
      auto pos = this->ddmf_.find(cbit.bitno_);
      assert(pos != this->ddmf_.end());
      DDMF control_one = pos->second;
      if(!cbit.polarity_) control_one = control_one ^ ddmf_not;
      control_logic = control_logic * control_one;
    }

    const auto& tbits = gate->getTbitList();
    for(const auto& tbit : tbits) {
      auto pos = this->ddmf_.find(tbit.bitno_);
      assert(pos != this->ddmf_.end());
      DDMF unitary = gate->getTargetUnitary() * ddmf_one;
      pos->second = pos->second ^ (control_logic * unitary);
    }
  }
}

/**
 * @fn void print(std::ostream& os) const
 * @brief print included quantum gates
 * @param [in] os output stream object
 */
void Step::print(std::ostream& os) const {
  for(const auto& gate : this->gates_)
    gate->print(os);
}
}
