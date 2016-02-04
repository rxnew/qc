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
  auto getGateListBegin() -> IterGateList;
  auto getGateListEnd() -> IterGateList;
  auto addGate(GatePtr&& gate) -> void;
  auto addGate(GatePtr& gate) -> void;
  auto addGate(Gate*&& gate) -> void;
  auto insertGate(CIterGateList pos, GatePtr&& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, GatePtr& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, Gate*&& gate) -> IterGateList;
  auto eraseGate(CIterGateList pos) -> IterGateList;
  auto eraseGate(IterGateList pos, GatePtr& gate) -> IterGateList;
  auto eraseGate(CIterGateList first, CIterGateList last) -> IterGateList;
  auto swapGate(IterGateList pos1, IterGateList pos2) -> void;
  auto append(const Circuit& circ) -> void;
  auto clear() -> void;
  auto getGateCount() const -> size_t;
  auto collectUsedBits() const -> BitList;
  auto computeMatrix() const -> Matrix;
  auto computeZeroVectorMap() const -> std::map<Bitno, Vector>;
  auto simulate() const -> Vector;
  auto simulate(const Vector& input) const -> Vector;
  auto simulate(const Vector& input, const Matrix& matrix) const -> Vector;
  auto simulate(std::vector<Complex>&& input) const -> Vector;
  auto simulate(const std::map<Bitno, Vector>& input) const -> Vector;
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

inline auto Circuit::getGateListBegin() -> IterGateList {
  return this->gates_.begin();
}

inline auto Circuit::getGateListEnd() -> IterGateList {
  return this->gates_.end();
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

inline auto Circuit::eraseGate(IterGateList pos, GatePtr& gate)
  -> IterGateList {
  gate = std::move(*pos);
  return this->eraseGate(pos);
}

inline auto Circuit::eraseGate(CIterGateList first, CIterGateList last)
  -> IterGateList {
  return this->gates_.erase(first, last);
}

inline auto Circuit::swapGate(IterGateList pos1, IterGateList pos2) -> void {
  assert(pos1 != this->gates_.end());
  assert(pos2 != this->gates_.end());
  std::swap(*pos1, *pos2);
}

inline auto Circuit::clear() -> void {
  this->gates_.clear();
}

inline auto Circuit::getGateCount() const -> size_t {
  return this->gates_.size();
}

inline auto Circuit::computeZeroVectorMap() const -> std::map<Bitno, Vector> {
  using util::container::toMap;
  using util::matrix::ket;
  return std::move(toMap<Vector>(this->collectUsedBits(), ket<0>()));
}

inline auto Circuit::simulate() const -> Vector {
  return this->simulate(this->computeZeroVectorMap());
}

inline auto Circuit::simulate(const Vector& input, const Matrix& matrix) const
  -> Vector {
  assert(input.rows() == matrix.cols());
  return std::move(matrix * input);
}

inline auto Circuit::simulate(std::vector<Complex>&& input) const -> Vector {
  return this->simulate(util::matrix::createVector(std::move(input)));
}
}
