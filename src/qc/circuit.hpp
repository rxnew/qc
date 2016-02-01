/**
 * @file circuit.hpp
 * @brief header of the quantum circuit class
 */

#pragma once

#include <list>

#include "gate.hpp"

namespace qc {
class Circuit;

using GateList = std::list<GatePtr>;
using IterGateList = GateList::iterator;
using CIterGateList = GateList::const_iterator;
using CircuitPtr = std::shared_ptr<Circuit>;

/**
 * @brief quantum circuit class
 */
class Circuit {
 private:
  GateList gates_;

 public:
  Circuit();
  Circuit(const Circuit& other);
  virtual ~Circuit();
  auto operator=(const Circuit& other) -> Circuit&;
  auto operator==(const Circuit& other) const -> bool;
  auto operator!=(const Circuit& other) const -> bool;
  auto getGateList() const -> const GateList&;
  auto addGate(const GatePtr& gate) -> void;
  auto addGate(Gate*&& gate) -> void;
  auto insertGate(CIterGateList pos, const GatePtr& gate) -> CIterGateList;
  auto insertGate(CIterGateList pos, Gate*&& gate) -> CIterGateList;
  auto eraseGate(CIterGateList pos) -> CIterGateList;
  auto removeGate(const GatePtr& gate) -> void;
  auto append(const Circuit& circ) -> void;
  auto getGateCount() const -> int;
  auto getUsedBits() const -> BitList;
  auto findGate(const GatePtr& gate) const -> CIterGateList;
  auto isIncluded(const GatePtr& gate) const -> bool;
  auto computeMatrix() const -> Matrix;
  auto print(std::ostream& os) const -> void;
};

inline auto Circuit::getGateList() const -> const GateList& {
  return this->gates_;
}

inline auto Circuit::addGate(const GatePtr& gate) -> void {
  assert(gate);
  this->gates_.push_back(gate);
}

inline auto Circuit::addGate(Gate*&& gate) -> void {
  assert(gate != nullptr);
  this->gates_.emplace_back(gate);
}

inline auto Circuit::insertGate(CIterGateList pos, const GatePtr& gate)
  -> CIterGateList {
  assert(pos != this->gates_.cend());
  assert(gate);
  return this->gates_.insert(pos, gate);
}

inline auto Circuit::insertGate(CIterGateList pos, Gate*&& gate)
  -> CIterGateList {
  assert(pos != this->gates_.cend());
  assert(gate != nullptr);
  return this->gates_.emplace(pos, gate);
}

inline auto Circuit::eraseGate(CIterGateList pos) -> CIterGateList {
  return this->gates_.erase(pos);
}

inline auto Circuit::removeGate(const GatePtr& gate) -> void {
  this->gates_.remove(gate);
}

inline auto Circuit::getGateCount() const -> int {
  return static_cast<int>(this->gates_.size());
}

inline auto Circuit::findGate(const GatePtr& gate) const -> CIterGateList {
  return std::find(this->gates_.cbegin(), this->gates_.cend(), gate);
}

inline auto Circuit::isIncluded(const GatePtr& gate) const -> bool {
  return this->gates_.cend() != this->findGate(gate);
}
}
