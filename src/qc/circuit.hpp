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
  auto addGate(const GatePtr& gate) -> void;
  auto addGate(Gate*&& gate) -> void;
  auto insertGate(CIterGateList pos, const GatePtr& gate) -> CIterGateList;
  auto insertGate(CIterGateList pos, Gate*&& gate) -> CIterGateList;
  auto insertGate(const GatePtr& pos, const GatePtr& gate) -> void;
  auto insertGate(const GatePtr& pos, Gate*&& gate) -> void;
  auto eraseGate(const GatePtr& gate) -> void;
  auto eraseGate(CIterGateList pos) -> CIterGateList;
  auto append(const Circuit& circ) -> void;
  auto getFirstGate() const -> GatePtr;
  auto getLastGate() const -> GatePtr;
  auto getAnyGate(int n) const -> GatePtr;
  auto getGateIndex(const GatePtr& gate) const -> int;
  auto getGateCount() const -> int;
  auto getUsedBits() const -> BitList;
  auto findGate(const GatePtr& gate) const -> CIterGateList;
  auto isExistGate(const GatePtr& gate) const -> bool;
  auto getMatrix() const -> Matrix;
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

inline auto Circuit::insertGate(const GatePtr& pos, const GatePtr& gate)
  -> void {
  insertGate(this->findGate(pos), gate);
}

inline auto Circuit::insertGate(const GatePtr& pos, Gate*&& gate) -> void {
  insertGate(this->findGate(pos), std::move(gate));
}

inline auto Circuit::eraseGate(const GatePtr& gate) -> void {
  this->gates_.remove(gate);
}

inline auto Circuit::eraseGate(CIterGateList pos) -> CIterGateList {
  return this->gates_.erase(pos);
}

inline auto Circuit::getFirstGate() const -> GatePtr {
  return this->gates_.front();
}

inline auto Circuit::getLastGate() const -> GatePtr {
  return this->gates_.back();
}

inline auto Circuit::getGateCount() const -> int {
  return static_cast<int>(this->gates_.size());
}

inline auto Circuit::findGate(const GatePtr& gate) const -> CIterGateList {
  return std::find(this->gates_.cbegin(), this->gates_.cend(), gate);
}

inline auto Circuit::isExistGate(const GatePtr& gate) const -> bool {
  return this->gates_.cend() != this->findGate(gate);
}
}
