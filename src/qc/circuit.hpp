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
  ~Circuit();
  auto operator=(const Circuit& other) -> Circuit&;
  auto operator==(const Circuit& other) const -> bool;
  auto operator!=(const Circuit& other) const -> bool;
  auto getGateList() const -> const GateList&;
  auto addGate(GatePtr&& gate) -> void;
  auto addGate(GatePtr& gate) -> void;
  auto addGate(Gate*&& gate) -> void;
  auto insertGate(CIterGateList pos, GatePtr&& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, GatePtr& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, Gate*&& gate) -> IterGateList;
  auto eraseGate(CIterGateList pos) -> IterGateList;
  auto append(const Circuit& circ) -> void;
  auto getGateCount() const -> size_t;
  auto collectUsedBits() const -> BitList;
  auto computeMatrix() const -> Matrix;
  auto print(std::ostream& os = std::cout) const -> void;
};

inline Circuit::Circuit() {
}

inline Circuit::~Circuit() {
}

inline auto Circuit::operator!=(const Circuit& other) const -> bool {
  return !(*this == other);
}

inline auto Circuit::getGateList() const -> const GateList& {
  return this->gates_;
}

inline auto Circuit::addGate(GatePtr&& gate) -> void {
  assert(gate);
  this->gates_.push_back(std::move(gate));
}

inline auto Circuit::addGate(GatePtr& gate) -> void {
  this->addGate(std::move(gate));
}

inline auto Circuit::addGate(Gate*&& gate) -> void {
  assert(gate != nullptr);
  this->gates_.emplace_back(gate);
}

inline auto Circuit::insertGate(CIterGateList pos, GatePtr&& gate)
  -> IterGateList {
  assert(gate);
  return this->gates_.insert(pos, std::move(gate));
}

inline auto Circuit::insertGate(CIterGateList pos, GatePtr& gate)
  -> IterGateList {
  return this->insertGate(pos, std::move(gate));
}

inline auto Circuit::insertGate(CIterGateList pos, Gate*&& gate)
  -> IterGateList {
  assert(gate != nullptr);
  return this->gates_.emplace(pos, gate);
}

inline auto Circuit::eraseGate(CIterGateList pos) -> IterGateList {
  return this->gates_.erase(pos);
}

inline auto Circuit::getGateCount() const -> size_t {
  return this->gates_.size();
}
}
