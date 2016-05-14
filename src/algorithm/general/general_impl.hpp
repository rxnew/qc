/**
 * @file general_impl.hpp
 * @brief implementation header general algorithm
 */

#pragma once

namespace qc {
template <class... Args>
auto createGate(const std::string& str, Args&&... args) -> GatePtr {
  const auto& gate_type = qc::getGateTypeName(str);

#define IF_GEN(type) \
  if(util::string::equalCaseInsensitive(gate_type, type::TYPE_NAME)) \
    return GatePtr(new type(std::forward<Args>(args)...))

  IF_GEN(I);
  IF_GEN(X);
  IF_GEN(Z);
  IF_GEN(V);
  IF_GEN(VPlus);
  IF_GEN(S);
  IF_GEN(T);
  IF_GEN(Hadamard);
  IF_GEN(Swap);

#undef IF_GEN

  return GatePtr(nullptr);
}

template <class... Args>
inline auto createGate(const Matrix& target_matrix, Args&&... args) -> GatePtr {
  return GatePtr(new U(std::forward<Args>(args)...));
}

inline auto getCbit(const GatePtr& gate) -> const Cbit& {
  assert(gate->isSingleControlled());
  return *gate->getCbitList().cbegin();
}

inline auto getTbit(const GatePtr& gate) -> const Tbit& {
  assert(gate->isSingleTarget());
  return *gate->getTbitList().cbegin();
}
}
