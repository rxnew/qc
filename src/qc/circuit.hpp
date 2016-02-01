/**
 * @file circuit.hpp
 * @brief header of the quantum circuit class
 */

#pragma once

#include <list>

#include "gate.hpp"

namespace qc {
class Circuit;

using CircuitPtr = std::shared_ptr<Circuit>;

using IterGateList = GateList::iterator;
using CIterGateList = GateList::const_iterator;

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
  auto addGate(const Gate& gate) -> void;
  auto addGate(Gate&& gate) -> void;
  auto insertGate(CIterGateList pos, const Gate& gate) -> CIterGateList;
  auto insertGate(CIterGateList pos, Gate&& gate) -> CIterGateList;
  auto eraseGate(CIterGateList pos) -> CIterGateList;
  auto removeGate(const Gate& gate) -> void;
  auto swapGate(CIterGateList pos1, CIterGateList pos2) -> void;
  auto append(const Circuit& circ) -> void;
  auto getCIterGateListBegin() const -> CIterGateList;
  auto getCIterGateListEnd() const -> CIterGateList;
  auto getGateCount() const -> int;
  auto getUsedBits() const -> BitList;
  auto findGate(const Gate& gate) const -> CIterGateList;
  auto isIncluded(const Gate& gate) const -> bool;
  auto computeMatrix() const -> Matrix;
  auto print(std::ostream& os) const -> void;
};

inline auto Circuit::getGateList() const -> const GateList& {
  return this->gates_;
}

inline auto Circuit::addGate(const Gate& gate) -> void {
  this->gates_.push_back(gate);
}

inline auto Circuit::addGate(Gate&& gate) -> void {
  this->gates_.push_back(gate);
}

inline auto Circuit::insertGate(CIterGateList pos, const Gate& gate)
  -> CIterGateList {
  return this->gates_.insert(pos, gate);
}

inline auto Circuit::insertGate(CIterGateList pos, Gate&& gate)
  -> CIterGateList {
  return this->gates_.insert(pos, gate);
}

inline auto Circuit::eraseGate(CIterGateList pos) -> CIterGateList {
  return this->gates_.erase(pos);
}

inline auto Circuit::removeGate(const Gate& gate) -> void {
  this->gates_.remove(gate);
}

inline auto Circuit::getCIterGateListBegin() const -> CIterGateList {
  return this->gates_.cbegin();
}

inline auto Circuit::getCIterGateListEnd() const -> CIterGateList {
  return this->gates_.cend();
}

inline auto Circuit::getGateCount() const -> int {
  return static_cast<int>(this->gates_.size());
}

inline auto Circuit::findGate(const Gate& gate) const -> CIterGateList {
  return std::find(this->gates_.cbegin(), this->gates_.cend(), gate);
}

inline auto Circuit::isIncluded(const Gate& gate) const -> bool {
  return this->gates_.cend() != this->findGate(gate);
}
}
