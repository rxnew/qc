/**
 * @file gate.hpp
 * @brief header of quantum gate classes
 */

#pragma once

#include <set>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>

#include "container.hpp"
#include "string.hpp"
#include "matrix.hpp"

#include "bit.hpp"

namespace qc {
class Gate;

using BitList = std::unordered_set<Bitno>;
using CbitList = std::unordered_set<Cbit>;
using TbitList = std::unordered_set<Tbit>;
using GatePtr = std::unique_ptr<Gate>;

using util::matrix::Complex;
using util::matrix::Matrix;
using util::matrix::Vector;
using util::matrix::operator"" _i;

/**
 * @brief quantum gate class
 * @note this class is abstract
 */
class Gate {
 private:
  class MatrixMap;

  using ui = unsigned int;

  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 protected:
  CbitList cbits_;
  TbitList tbits_;

  Gate(const Tbit& tbit);
  Gate(const Tbit& tbit1, const Tbit& tbit2);
  Gate(const Cbit& cbit, const Tbit& tbit);
  Gate(const Cbit& cbit, const TbitList& tbits);
  Gate(const Cbit& cbit, TbitList&& tbits);
  Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  Gate(const CbitList& cbits, const Tbit& tbit);
  Gate(CbitList&& cbits, const Tbit& tbit);
  Gate(const CbitList& cbits, const TbitList& tbits);
  Gate(CbitList&& cbits, TbitList&& tbits);
  Gate(const Gate& other);
  Gate(Gate&&) noexcept = default;

  auto _computeMatrix(const MatrixMap& matrix_map) const -> Matrix;
  auto _simulate(const Vector& input, const MatrixMap& matrix_map) const
    -> Vector;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  virtual ~Gate();
  auto operator=(const Gate& other) -> Gate&;
  auto operator=(Gate&& other) -> Gate&;
  auto operator==(const Gate& other) const -> bool;
  auto operator!=(const Gate& other) const -> bool;
  virtual auto clone() const -> GatePtr = 0;
  virtual auto getTypeName() const -> const std::string& = 0;
  auto getCbitList() const -> const CbitList&;
  auto getTbitList() const -> const TbitList&;
  auto setCbits(const CbitList& cbits) -> void;
  auto setCbits(CbitList&& cbits) -> void;
  auto setTbits(const TbitList& tbits) -> void;
  auto setTbits(TbitList&& tbits) -> void;
  auto isIncludedInCbitList(Bitno bit) const -> bool;
  auto isIncludedInTbitList(Bitno bit) const -> bool;
  auto collectUsedBits() const -> BitList;
  virtual auto getTargetMatrix() const -> const Matrix& = 0;
  virtual auto computeMatrix(const std::set<Bitno>& bits) const -> Matrix;
  auto computeMatrix(const BitList& bits) const -> Matrix;
  auto computeMatrix() const -> Matrix;
  auto simulate(const Vector& input, const std::set<Bitno>& bits) const
    -> Vector;
  auto simulate(const Vector& input, const BitList& bits) const -> Vector;
  auto simulate(const Vector& input) const -> Vector;
  auto isAllPositive() const -> bool;
  auto print(std::ostream& os = std::cout) const -> void;

 private:
  class MatrixMap {
   private:
    const Gate& gate_;
    ui active_polarity_pattern_;
    ui polarity_pattern_mask_;

    auto _init() -> void;
    auto _setActivePolarityPattern() -> void;
    auto _updateActive(bool is_cbit, Bitno bit) -> void;
    auto _updateInactive(bool is_cbit) -> void;
    auto _mask(ui polarity_pattern) const -> bool;
    auto _isActive() const -> bool;

   public:
    // matrix of active input pattern of each target
    std::unordered_map<Bitno, Matrix> active_;
    // matrix of inactive each input pattern
    std::unordered_map<ui, Matrix> inactive_;

    MatrixMap(const Gate& gate, const std::set<Bitno>& bits);
  };
};

/**
 * @brief V gate class
 */
class V : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  V(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief V+ gate class
 */
class VPlus : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  VPlus(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Hadamard gate class
 */
class Hadamard : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Hadamard(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Not gate class
 */
class Not : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Not(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Z gate class
 */
class Z : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Z(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Swap gate class
 */
class Swap : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Swap(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
  auto computeMatrix(const std::set<Bitno>& bits) const -> Matrix;
  auto decompose() const -> std::list<GatePtr>;
};

/**
 * @brief T gate class
 */
class T : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  T(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief GateBuilder class
 */
struct GateBuilder {
  template <class... Args>
  static auto create(const std::string& str, Args&&... args) -> GatePtr;
};

//implementation
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

inline Gate::Gate(const Gate& other)
  : cbits_(other.cbits_), tbits_(other.tbits_) {
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

inline auto Gate::MatrixMap::_mask(ui polarity_pattern) const -> bool {
  return polarity_pattern & polarity_pattern_mask_;
}

inline auto Gate::MatrixMap::_isActive() const -> bool {
  return this->_mask(this->active_polarity_pattern_);
}

inline auto V::_createTargetMatrixList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 0.5 + 0.5_i;
  constexpr auto b = 0.5 - 0.5_i;
  return {a, b, b, a};
}

template <class... Args>
V::V(Args&&... args) : Gate(args...) {}

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
VPlus::VPlus(Args&&... args) : Gate(args...) {}

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
Hadamard::Hadamard(Args&&... args) : Gate(args...) {
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
Not::Not(Args&&... args) : Gate(args...) {}

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
Z::Z(Args&&... args) : Gate(args...) {}

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
Swap::Swap(Args&&... args) : Gate(args...) {
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
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, 1.0_i};
}

template <class... Args>
T::T(Args&&... args) : Gate(args...) {}

inline auto T::clone() const -> GatePtr {
  return GatePtr(new T(*this));
}

inline auto T::getTypeName() const -> const std::string& {
  return T::TYPE_NAME;
}

inline auto T::getTargetMatrix() const -> const Matrix& {
  return T::TARGET_MATRIX;
}

template <class... Args>
auto GateBuilder::create(const std::string& str, Args&&... args) -> GatePtr {
#define IF_GEN(type) \
  if(util::string::equalCaseInsensitive(str, type::TYPE_NAME)) \
    return GatePtr(new type(args...))

  IF_GEN(V);
  IF_GEN(VPlus);
  IF_GEN(Hadamard);
  IF_GEN(Not);
  IF_GEN(Z);
  IF_GEN(Swap);
  IF_GEN(T);

#undef IF_GEN

  return GatePtr(nullptr);
}
}
