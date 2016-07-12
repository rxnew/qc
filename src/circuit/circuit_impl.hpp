/**
 * @file circuit_impl.hpp
 * @brief implementation header of Circuit class
 */

#pragma once

namespace qc {
template <class stringT>
inline Circuit::Circuit(stringT&& description)
  : description_(std::forward<stringT>(description)) {
}

template <class stringT>
inline Circuit::Circuit(GateList&& gates, stringT&& description)
  : gates_(std::move(gates)), description_(std::forward<stringT>(description)) {
}

template <class GateListT, class stringT>
inline Circuit::Circuit(const GateListT& gates, stringT&& description)
  : description_(std::forward<stringT>(description)) {
  this->addGate(gates);
}

inline Circuit::Circuit(const Circuit& other) {
  *this = other;
}

inline auto Circuit::operator!=(const Circuit& other) const -> bool {
  return !(*this == other);
}

inline auto Circuit::getDescription() const -> const std::string& {
  return this->description_;
}

template <class stringT>
inline auto Circuit::setDescription(stringT&& description) -> void {
  this->description_ = std::forward<stringT>(description);
}

inline auto Circuit::getGateList() -> GateList& {
  return this->gates_;
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

inline auto Circuit::addGate(GateList&& gates) -> void {
  this->insertGate(this->gates_.cend(), std::move(gates));
}

template <class GateListT>
inline auto Circuit::addGate(const GateListT& gates) -> void {
  this->insertGate(this->gates_.cend(), gates);
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

inline auto Circuit::insertGate(CIterGateList pos, GateList&& gates)
  -> IterGateList {
  return this->gates_.insert(pos,
                             std::make_move_iterator(gates.begin()),
                             std::make_move_iterator(gates.end()));
}

template <class GateListT>
auto Circuit::insertGate(CIterGateList pos,
                         const GateListT& gates) -> IterGateList {
  auto result_pos = this->gates_.end();
  for(const auto& gate : gates) {
    auto tmp_pos = this->insertGate(pos, gate->clone());
    if(result_pos == this->gates_.end()) result_pos = tmp_pos;
  }
  return result_pos;
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

inline auto Circuit::append(const Circuit& circuit) -> void {
  this->addGate(circuit.gates_);
}

inline auto Circuit::append(Circuit&& circuit) -> void {
  this->addGate(std::move(circuit.gates_));
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
