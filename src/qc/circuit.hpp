/**
 * @file circuit.hpp
 * @brief header of the quantum circuit class
 */

#pragma once

#include <fstream>

#include "gate.hpp"

namespace qc {
class Circuit;

using CircuitPtr = std::shared_ptr<Circuit>;

using GateList = std::list<GatePtr>;
using IterGateList = GateList::iterator;
using CIterGateList = GateList::const_iterator;

/**
 * @brief quantum circuit class
 */
class Circuit {
 protected:
  GateList gates_;

 public:
  Circuit();
  Circuit(const Circuit& other);
  virtual ~Circuit();
  Circuit& operator=(const Circuit& other);
  bool operator==(const Circuit& other) const;
  bool operator!=(const Circuit& other) const;
  inline const GateList& getGateList() const {
    return this->gates_;
  }
  inline void addGate(const GatePtr& gate) {
    assert(gate.get() != nullptr);
    this->gates_.push_back(gate);
  }
  inline void addGate(Gate*&& gate) {
    assert(gate != nullptr);
    this->gates_.emplace_back(gate);
  }
  inline CIterGateList insertGate(CIterGateList pos, const GatePtr& gate) {
    assert(pos != this->gates_.cend());
    assert(gate.get() != nullptr);
    return this->gates_.insert(pos, gate);
  }
  inline CIterGateList insertGate(CIterGateList pos, Gate*&& gate) {
    assert(pos != this->gates_.cend());
    assert(gate != nullptr);
    return this->gates_.emplace(pos, gate);
  }
  inline void insertGate(const GatePtr& pos, const GatePtr& gate) {
    insertGate(this->findGate(pos), gate);
  }
  inline void insertGate(const GatePtr& pos, Gate*&& gate) {
    insertGate(this->findGate(pos), std::move(gate));
  }
  inline void eraseGate(const GatePtr& gate) {
    this->gates_.remove(gate);
  }
  inline CIterGateList eraseGate(CIterGateList pos) {
    return this->gates_.erase(pos);
  }
  inline void append(const Circuit& circ) {
    for(const auto& gate : circ.gates_)
      this->addGate(gate->clone());
  }
  inline GatePtr getFirstGate() const {
    return this->gates_.front();
  }
  inline GatePtr getLastGate() const {
    return this->gates_.back();
  }
  GatePtr getAnyGate(int n) const;
  int getGateIndex(const GatePtr& gate) const;
  inline int getGateCount() const {
    return this->gates_.size();
  };
  BitList getUsedBits() const;
  inline CIterGateList findGate(const GatePtr& gate) const {
    return std::find(this->gates_.cbegin(), this->gates_.cend(), gate);
  }
  inline bool isExistGate(const GatePtr& gate) const {
    return this->gates_.cend() != this->findGate(gate);
  }
  inline void print(std::ostream& os) const {
    for(const auto& gate : this->gates_)
      gate->print(os);
  }
  void open(const std::string& filename) {}
  void open(const char* filename) {}
};
}
