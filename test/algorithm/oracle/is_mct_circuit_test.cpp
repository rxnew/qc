#include "gtest/gtest.h"

#include "circuit.hpp"
#include "gate/library.hpp"
#include "algorithm/oracle.hpp"

using namespace qc::literals;
using namespace qc::library_gates;
using qc::is_mct_circuit;
using qc::Gate;

TEST(IsMctCircuitTest, TrueCase) {
  auto gates = qc::Gates{Gate::make<X>(0_tbit), Gate::make<X>(0_cbit, 1_tbit)};
  auto circuit = qc::Circuit(std::move(gates));
  EXPECT_TRUE(is_mct_circuit(circuit));
}

TEST(IsMctCircuitTest, FalseCase) {
  auto gates = qc::Gates{Gate::make<V>(0_tbit), Gate::make<X>(0_cbit, 1_tbit)};
  auto circuit = qc::Circuit(std::move(gates));
  EXPECT_FALSE(is_mct_circuit(circuit));
}
