/**
 * @file general_impl.hpp
 * @brief implementation header general algorithm
 */

#pragma once

namespace qc {
template <class GatePtrT = GatePtr, class... Args>
auto createGate(const std::string& str, Args&&... args) -> GatePtrT {
  const auto& gate_type = qc::getGateTypeName(str);

#define IF_GEN(type) \
  if(util::string::equalCaseInsensitive(gate_type, type::TYPE_NAME)) \
    return GatePtrT(new type(std::forward<Args>(args)...))

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

  return GatePtrT(nullptr);
}

template <class GatePtrT = GatePtr, class... Args>
inline auto createGate(const Matrix& target_matrix,
                       Args&&... args) -> GatePtrT {
  return GatePtrT(new U(std::forward<Args>(args)...));
}

template <class GatePtrT>
inline auto getCbit(const GatePtrT& gate) -> const Cbit& {
  assert(gate->isSingleControlled());
  return *gate->getCbitList().cbegin();
}

template <class GatePtrT>
inline auto getTbit(const GatePtrT& gate) -> const Tbit& {
  assert(gate->isSingleTarget());
  return *gate->getTbitList().cbegin();
}

template <class GatePtrT, class GateListT = std::list<GatePtrT>>
auto decompIntoSingleTargetGates(const GatePtrT& gate) -> GateListT {
  const auto& gate_type_name = gate->getTypeName();
  const auto& cbits = gate->getCbitList();
  const auto& tbits = gate->getTbitList();
  GateListT result;
  for(const auto& tbit : tbits) {
    result.push_back(qc::createGate(gate_type_name, cbits, tbit));
  }
  return std::move(result);
}
}
