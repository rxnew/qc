/**
 * @file gate.hpp
 * @brief header of quantum gate classes
 */

#pragma once

#include <set>
#include <unordered_set>
#include <memory>
#include <algorithm>

#include "container.hpp"
#include "string.hpp"
#include "eigen.hpp"

#include "bit.hpp"

namespace qc {
class Gate;

using GatePtr = std::shared_ptr<Gate>;
using BitList = std::unordered_set<Bitno>;
using CbitList = std::unordered_set<Cbit>;
using TbitList = std::unordered_set<Tbit>;

using util::eigen::Complex;
using util::eigen::Unitary;
using util::eigen::operator"" _i;

/**
 * @brief quantum gate class
 * @note this class is abstract
 */
class Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 protected:
  CbitList cbits_;
  TbitList tbits_;

  Gate(const Tbit& tbit);
  Gate(const Tbit& tbit1, const Tbit& tbit2);
  Gate(const Cbit& cbit, const Tbit& tbit);
  Gate(const Cbit& cbit, const TbitList& tbits);
  Gate(const Cbit& cbit, const std::initializer_list<Tbit>& tbits);
  Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  Gate(const CbitList& cbits, const Tbit& tbit);
  Gate(const std::initializer_list<Cbit>& cbits, const Tbit& tbit);
  Gate(const CbitList& cbits, const TbitList& tbits);
  Gate(const std::initializer_list<Cbit>& cbits, \
       const std::initializer_list<Tbit>& tbits);
  Gate(const Gate& other);

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  virtual ~Gate();
  auto operator=(const Gate& other) -> Gate&;
  auto operator==(const Gate& other) const -> bool;
  auto operator!=(const Gate& other) const -> bool;
  virtual auto clone() const -> GatePtr = 0;
  virtual auto getTypeName() const -> const std::string& = 0;
  auto getCbitList() const -> const CbitList&;
  auto getTbitList() const -> const TbitList&;
  auto setCbits(const CbitList& cbits) -> void;
  auto setTbits(const TbitList& tbits) -> void;
  virtual auto getTargetUnitary() const -> const Unitary& = 0;
  auto getUsedBits() const -> BitList;
  auto isAllPositive() const -> bool;
  auto print(std::ostream& os) const -> void;
};

inline auto Gate::_createTargetUnitaryList()
  -> std::initializer_list<Complex> {
  return {};
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

inline auto Gate::setTbits(const TbitList& tbits) -> void {
  this->tbits_ = tbits;
}

/**
 * @brief V gate class
 * @note gate type is 16
 */
class V : public Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  template <class... Args>
  V(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetUnitary() const -> const Unitary&;
};

inline auto V::_createTargetUnitaryList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 0.5 + 0.5_i;
  constexpr auto b = 0.5 - 0.5_i;
  return {a, b, b, a};
}

template <class... Args>
V::V(Args&&... args) : Gate(args...) {}

inline auto V::clone() const -> GatePtr {
  return std::move(std::make_shared<V>(*this));
}

inline auto V::getTypeName() const -> const std::string& {
  return V::TYPE_NAME;
}

inline auto V::getTargetUnitary() const -> const Unitary& {
  return V::TARGET_UNITARY;
}

/**
 * @brief V+ gate class
 * @note gate type is 15
 */
class VPlus : public Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  template <class... Args>
  VPlus(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetUnitary() const -> const Unitary&;
};

inline auto VPlus::_createTargetUnitaryList()
  -> std::initializer_list<Complex> {
  constexpr auto a = 0.5 + 0.5_i;
  constexpr auto b = 0.5 - 0.5_i;
  return {b, a, a, b};
}

template <class... Args>
VPlus::VPlus(Args&&... args) : Gate(args...) {}

inline auto VPlus::clone() const -> GatePtr {
  return std::move(std::make_shared<VPlus>(*this));
}

inline auto VPlus::getTypeName() const -> const std::string& {
  return VPlus::TYPE_NAME;
}

inline auto VPlus::getTargetUnitary() const -> const Unitary& {
  return VPlus::TARGET_UNITARY;
}

/**
 * @brief Hadamard gate class
 * @note gate type is 1
 */
class Hadamard : public Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  template <class... Args>
  Hadamard(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetUnitary() const -> const Unitary&;
};

inline auto Hadamard::_createTargetUnitaryList()
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
  return std::move(std::make_shared<Hadamard>(*this));
}

inline auto Hadamard::getTypeName() const -> const std::string& {
  return Hadamard::TYPE_NAME;
}

inline auto Hadamard::getTargetUnitary() const -> const Unitary& {
  return Hadamard::TARGET_UNITARY;
}

/**
 * @brief NOT gate class
 * @note gate type is 2
 */
class Not : public Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  template <class... Args>
  Not(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetUnitary() const -> const Unitary&;
};

inline auto Not::_createTargetUnitaryList()
  -> std::initializer_list<Complex> {
  return {0, 1, 1, 0};
}

template <class... Args>
Not::Not(Args&&... args) : Gate(args...) {}

inline auto Not::clone() const -> GatePtr {
  return std::move(std::make_shared<Not>(*this));
}

inline auto Not::getTypeName() const -> const std::string& {
  return Not::TYPE_NAME;
}

inline auto Not::getTargetUnitary() const -> const Unitary& {
  return Not::TARGET_UNITARY;
}

/**
 * @brief Z gate class
 * @note gate type is 6
 */
class Z : public Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  template <class... Args>
  Z(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetUnitary() const -> const Unitary&;
};

inline auto Z::_createTargetUnitaryList()
  -> std::initializer_list<Complex> {
  return {1, 0, 0, -1};
}

template <class... Args>
Z::Z(Args&&... args) : Gate(args...) {}

inline auto Z::clone() const -> GatePtr {
  return std::move(std::make_shared<Z>(*this));
}

inline auto Z::getTypeName() const -> const std::string& {
  return Z::TYPE_NAME;
}

inline auto Z::getTargetUnitary() const -> const Unitary& {
  return Z::TARGET_UNITARY;
}

/**
 * @brief Swap gate class
 * @note gate type is 12
 */
class Swap : public Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  template <class... Args>
  Swap(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetUnitary() const -> const Unitary&;
};

inline auto Swap::_createTargetUnitaryList()
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
  return std::move(std::make_shared<Swap>(*this));
}

inline auto Swap::getTypeName() const -> const std::string& {
  return Swap::TYPE_NAME;
}

inline auto Swap::getTargetUnitary() const -> const Unitary& {
  return Swap::TARGET_UNITARY;
}

class T : public Gate {
 private:
  static auto _createTargetUnitaryList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Unitary TARGET_UNITARY;

  template <class... Args>
  T(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetUnitary() const -> const Unitary&;
};

inline auto T::_createTargetUnitaryList()
  -> std::initializer_list<Complex> {
  return {1.0 + 0.0_i, 0.0_i, 0.0_i, 1.0_i};
}

template <class... Args>
T::T(Args&&... args) : Gate(args...) {}

inline auto T::clone() const -> GatePtr {
  return std::move(std::make_shared<T>(*this));
}

inline auto T::getTypeName() const -> const std::string& {
  return T::TYPE_NAME;
}

inline auto T::getTargetUnitary() const -> const Unitary& {
  return T::TARGET_UNITARY;
}

struct GateBuilder {
  template <class... Args>
  static auto create(const std::string& str, Args&&... args) -> GatePtr;
};

template <class... Args>
auto GateBuilder::create(const std::string& str, Args&&... args) -> GatePtr {
#define IF_GEN(type) \
  if(util::string::equalCaseInsensitive(str, type::TYPE_NAME)) \
    return std::move(std::make_shared<type>(args...)) \

  IF_GEN(V);
  IF_GEN(VPlus);
  IF_GEN(Hadamard);
  IF_GEN(Not);
  IF_GEN(Z);
  IF_GEN(Swap);
  IF_GEN(T);

#undef IF_GEN

  return std::move(GatePtr(nullptr));
}
}

namespace std {
template <class T>
struct hash<unordered_set<T>> {
  auto operator()(const unordered_set<T>& obj) const -> size_t {
    size_t hash_value;
    for(const auto& elem : obj) {
      hash_value ^= hash<T>()(elem) + 0x9e3779b9 + (hash_value << 6);
    }
    return hash_value;
  }
};

template <>
struct hash<qc::Gate> {
  auto operator()(const qc::Gate& obj) const -> size_t {
    auto cbit_hash = hash<unordered_set<qc::Cbit>>()(obj.getCbitList());
    auto tbit_hash = hash<unordered_set<qc::Tbit>>()(obj.getTbitList());
    return cbit_hash ^ tbit_hash;
  }
};
}
