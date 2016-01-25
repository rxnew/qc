/**
 * @file step.hpp
 * @brief header of the calculation step class
 */

#pragma once

#include <list>
#include <map>
#include <algorithm>

#include "gate.hpp"

namespace qc {
class Step;

using StepPtr = std::shared_ptr<Step>;

using GateSet = std::unordered_set<GatePtr>;
using IterGateSet = GateSet::iterator;
using CIterGateSet = GateSet::const_iterator;

/**
 * @brief parallel quantum gate class
 */
class Step {
 private:
  GateSet gates_;
  std::map<Bitno, DDMF> ddmf_;

 public:
  Step();
  Step(const GatePtr& gate);
  Step(Gate*&& gate);
  Step(const GateSet& gates);
  Step(const Step& other);
  virtual ~Step();
  Step& operator=(const Step& other);
  bool operator==(const Step& other) const;
  bool operator!=(const Step& other) const;
  inline const GateSet& getGateSet() const {
    return this->gates_;
  }
  inline void addGate(const GatePtr& gate) {
    this->gates_.insert(gate);
  }
  inline void addGate(Gate*&& gate) {
    this->gates_.emplace(gate);
  }
  inline void eraseGate(const GatePtr& gate) {
    this->gates_.erase(gate);
  }
  inline CIterGateSet eraseGate(CIterGateSet pos) {
    return this->gates_.erase(pos);
  }
  inline void clear() {
    this->gates_.clear();
  }
  CIterGateSet findSameGate(const GatePtr& gate) const;
  BitList getUsedBits() const;
  inline CIterGateSet findGate(const GatePtr& gate) const {
    return this->gates_.find(gate);
  }
  inline bool isExistGate(const GatePtr& gate) const {
    return this->gates_.cend() != this->findGate(gate);
  }
  inline bool isEmpty() const {
    return this->gates_.empty();
  }
  inline bool isOnlyOneGate() const {
    return static_cast<int>(this->gates_.size()) == 1;
  }
  void calcDDMF(DDMFMgr& ddmf_mgr);
  void print(std::ostream& os) const;
  friend class Circuit;
};
}
