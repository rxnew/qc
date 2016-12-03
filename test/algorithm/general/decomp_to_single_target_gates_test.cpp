#include "gtest/gtest.h"

#include "circuit.hpp"
#include "gate/library.hpp"
#include "gate/group.hpp"
#include "algorithm/general.hpp"

using namespace qc::literals;
using namespace qc::library;
using qc::decomp_to_single_target_gates;
using qc::Gate;

class DecompToSingleTargetGatesTest : public ::testing::Test {
 protected:
  DecompToSingleTargetGatesTest()
    : gates_before_{Gate::make<X>({0_cbit}, {1_tbit, 2_tbit})},
      gates_after_{Gate::make<X>(0_cbit, 1_tbit), Gate::make<X>(0_cbit, 2_tbit)}
  {}

  qc::Gates gates_before_;
  qc::Gates gates_after_;
};

TEST_F(DecompToSingleTargetGatesTest, Group) {
  auto group = qc::Group::make(gates_before_);
  auto gates_after = decomp_to_single_target_gates(group);
  EXPECT_EQ(gates_after.size(), gates_after_.size());
}

TEST_F(DecompToSingleTargetGatesTest, Circuit) {
  auto circuit = qc::Circuit(gates_before_);
  auto gates_after = decomp_to_single_target_gates(circuit);
  EXPECT_EQ(gates_after.get_gates_count(), gates_after_.size());
}
