/**
 * @file gate_impl.hpp
 * @brief implementation header of quantum gate classes
 */

#pragma once

namespace qc {
inline auto Gate::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {};
}

inline Gate::Gate(const Tbit& tbit) : tbits_{tbit} {
}

inline Gate::Gate(const Tbit& tbit1, const Tbit& tbit2) : tbits_{tbit1, tbit2} {
}

inline Gate::Gate(const Cbit& cbit, const Tbit& tbit)
  : cbits_{cbit}, tbits_{tbit} {
}

inline Gate::Gate(const Cbit& cbit, const TbitList& tbits)
  : cbits_{cbit}, tbits_(tbits) {
}

inline Gate::Gate(const Cbit& cbit, TbitList&& tbits)
  : cbits_{cbit}, tbits_(std::move(tbits)) {
}

inline Gate::Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit)
  : cbits_{cbit1, cbit2}, tbits_{tbit} {
}

inline Gate::Gate(const CbitList& cbits, const Tbit& tbit) :
  cbits_(cbits), tbits_{tbit} {
}

inline Gate::Gate(CbitList&& cbits, const Tbit& tbit) :
  cbits_(std::move(cbits)), tbits_{tbit} {
}

inline Gate::Gate(const CbitList& cbits, const TbitList& tbits) :
  cbits_(cbits), tbits_(tbits) {
}

inline Gate::Gate(CbitList&& cbits, TbitList&& tbits) :
  cbits_(std::move(cbits)), tbits_(std::move(tbits)) {
}

inline auto Gate::operator!=(const Gate& other) const -> bool {
  return !(*this == other);
}

inline auto Gate::getCbitList() const -> const CbitList& {
  return this->cbits_;
}

inline auto Gate::getTbitList() const -> const TbitList& {
  return this->tbits_;
}

inline auto Gate::setCbits(const CbitList& cbits) -> void {
  this->cbits_ = cbits;
}

inline auto Gate::setCbits(CbitList&& cbits) -> void {
  this->cbits_ = std::move(cbits);
}

inline auto Gate::setTbits(const TbitList& tbits) -> void {
  this->tbits_ = tbits;
}

inline auto Gate::setTbits(TbitList&& tbits) -> void {
  this->tbits_ = std::move(tbits);
}

inline auto Gate::isIncludedInCbitList(Bitno bit) const -> bool {
  return \
    this->cbits_.count(Cbit(bit, true)) || \
    this->cbits_.count(Cbit(bit, false));
}

inline auto Gate::isIncludedInTbitList(Bitno bit) const -> bool {
  return this->tbits_.count(Tbit(bit));
}

inline auto Gate::computeMatrix(const std::set<Bitno>& bits) const -> Matrix {
  return std::move(this->_computeMatrix(MatrixMap(*this, bits)));
}

inline auto Gate::computeMatrix(const BitList& bits) const -> Matrix {
  return this->computeMatrix(util::container::convert<std::set>(bits));
}

inline auto Gate::computeMatrix() const -> Matrix {
  return this->computeMatrix(this->collectUsedBits());
}

inline auto Gate::simulate(const Vector& input, const std::set<Bitno>& bits) \
  const -> Vector {
  assert(input.rows() == std::pow(2, bits.size()));
  return std::move(this->_simulate(input, MatrixMap(*this, bits)));
}

inline auto Gate::simulate(const Vector& input, const BitList& bits) const
  -> Vector {
  auto ordered_bits = util::container::convert<std::set>(bits);
  return this->simulate(input, ordered_bits);
}

inline auto Gate::simulate(const Vector& input) const -> Vector {
  return this->simulate(input, this->collectUsedBits());
}

inline auto Gate::getComponents() const -> const GateList& {
  static GateList components;
  components.push_back(std::move(this->clone()));
  return components;
}

inline auto Gate::MatrixMap::_mask(ui polarity_pattern) const -> bool {
  return polarity_pattern & polarity_pattern_mask_;
}

inline auto Gate::MatrixMap::_isActive() const -> bool {
  return this->_mask(this->active_polarity_pattern_);
}

inline auto I::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, 1.0 + 0.0_i};
}

template <class... Args>
I::I(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline auto I::clone() const -> GatePtr {
  return GatePtr(new I(*this));
}

inline auto I::getTypeName() const -> const std::string& {
  return I::TYPE_NAME;
}

inline auto I::getTargetMatrix() const -> const Matrix& {
  return I::TARGET_MATRIX;
}

inline auto V::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 0.5 + 0.5_i;
  constexpr auto b = 0.5 - 0.5_i;
  return {a, b, b, a};
}

template <class... Args>
V::V(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline auto V::clone() const -> GatePtr {
  return GatePtr(new V(*this));
}

inline auto V::getTypeName() const -> const std::string& {
  return V::TYPE_NAME;
}

inline auto V::getTargetMatrix() const -> const Matrix& {
  return V::TARGET_MATRIX;
}

inline auto VPlus::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 0.5 + 0.5_i;
  constexpr auto b = 0.5 - 0.5_i;
  return {b, a, a, b};
}

template <class... Args>
VPlus::VPlus(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline auto VPlus::clone() const -> GatePtr {
  return GatePtr(new VPlus(*this));
}

inline auto VPlus::getTypeName() const -> const std::string& {
  return VPlus::TYPE_NAME;
}

inline auto VPlus::getTargetMatrix() const -> const Matrix& {
  return VPlus::TARGET_MATRIX;
}

inline auto Hadamard::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 1.0 / std::sqrt(2) + 0.0_i;
  return {a, a, a, -a};
}

template <class... Args>
Hadamard::Hadamard(Args&&... args) : Gate(std::forward<Args>(args)...) {
  assert(this->cbits_.empty());
  assert(static_cast<int>(this->tbits_.size()) == 1);
}

inline auto Hadamard::clone() const -> GatePtr {
  return GatePtr(new Hadamard(*this));
}

inline auto Hadamard::getTypeName() const -> const std::string& {
  return Hadamard::TYPE_NAME;
}

inline auto Hadamard::getTargetMatrix() const -> const Matrix& {
  return Hadamard::TARGET_MATRIX;
}

inline auto Not::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {0, 1, 1, 0};
}

template <class... Args>
Not::Not(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline auto Not::clone() const -> GatePtr {
  return GatePtr(new Not(*this));
}

inline auto Not::getTypeName() const -> const std::string& {
  return Not::TYPE_NAME;
}

inline auto Not::getTargetMatrix() const -> const Matrix& {
  return Not::TARGET_MATRIX;
}

inline auto Z::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1, 0, 0, -1};
}

template <class... Args>
Z::Z(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline auto Z::clone() const -> GatePtr {
  return GatePtr(new Z(*this));
}

inline auto Z::getTypeName() const -> const std::string& {
  return Z::TYPE_NAME;
}

inline auto Z::getTargetMatrix() const -> const Matrix& {
  return Z::TARGET_MATRIX;
}

inline auto Swap::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1, 0, 0, 0, \
          0, 0, 1, 0, \
          0, 1, 0, 0, \
          0, 0, 0, 1};
}

template <class... Args>
Swap::Swap(Args&&... args) : Gate(std::forward<Args>(args)...) {
  assert(static_cast<int>(this->tbits_.size()) == 2);
}

inline auto Swap::clone() const -> GatePtr {
  return GatePtr(new Swap(*this));
}

inline auto Swap::getTypeName() const -> const std::string& {
  return Swap::TYPE_NAME;
}

inline auto Swap::getTargetMatrix() const -> const Matrix& {
  return Swap::TARGET_MATRIX;
}

inline auto T::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, sprout::exp(std::atan(1.0) * 1.0_i)};
}

template <class... Args>
T::T(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline auto T::clone() const -> GatePtr {
  return GatePtr(new T(*this));
}

inline auto T::getTypeName() const -> const std::string& {
  return T::TYPE_NAME;
}

inline auto T::getTargetMatrix() const -> const Matrix& {
  return T::TARGET_MATRIX;
}

inline auto S::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, 1.0_i};
}

template <class... Args>
S::S(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline auto S::clone() const -> GatePtr {
  return GatePtr(new S(*this));
}

inline auto S::getTypeName() const -> const std::string& {
  return S::TYPE_NAME;
}

inline auto S::getTargetMatrix() const -> const Matrix& {
  return S::TARGET_MATRIX;
}

inline auto MacroGate::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  return {};
}

template <class... Args>
MacroGate::MacroGate(Args&&... args) : Gate(std::forward<Args>(args)...) {}

inline MacroGate::MacroGate(const MacroGate& other) : Gate(other) {
  for(const auto& gate : other.getComponents()) {
    this->components_.push_back(gate->clone());
  }
}

inline auto MacroGate::clone() const -> GatePtr {
  return GatePtr(new MacroGate(*this));
}

inline auto MacroGate::getTypeName() const -> const std::string& {
  return MacroGate::TYPE_NAME;
}

inline auto MacroGate::getTargetMatrix() const -> const Matrix& {
  return MacroGate::TARGET_MATRIX;
}

inline auto MacroGate::getComponents() const -> const GateList& {
  return this->components_;
}

template <class... Args>
auto GateBuilder::create(const std::string& str, Args&&... args) -> GatePtr {
#define IF_GEN(type) \
  if(util::string::equalCaseInsensitive(str, type::TYPE_NAME)) \
    return GatePtr(new type(std::forward<Args>(args)...))

  IF_GEN(I);
  IF_GEN(V);
  IF_GEN(VPlus);
  IF_GEN(Hadamard);
  IF_GEN(Not);
  IF_GEN(Z);
  IF_GEN(Swap);
  IF_GEN(T);
  IF_GEN(S);

#undef IF_GEN

  return GatePtr(nullptr);
}
}
