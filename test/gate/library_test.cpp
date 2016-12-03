#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"

using namespace qc::literals;
using namespace qc::library;
using qc::Gate;
using qc::GateType;

class LibraryTest : public ::testing::Test {
 protected:
  LibraryTest() : x_(X(0_tbit)), v_(V(0_tbit)) {}

  Gate x_;
  Gate v_;
};

TEST_F(LibraryTest, MakeGate) {
  EXPECT_EQ(qc::make_gate(GateType::X, 0_tbit), x_);
  EXPECT_EQ(qc::make_gate(X::TYPE_NAME, 0_tbit), x_);
  auto x1 = Gate(X(0_cbit, 1_tbit));
  EXPECT_EQ(qc::make_gate(GateType::X, 0_cbit, 1_tbit), x1);
  EXPECT_EQ(qc::make_gate(X::TYPE_NAME, 0_cbit, 1_tbit), x1);
  auto x2 = Gate(X{{0_cbit, 1_cbit}, {3_tbit}});
  EXPECT_EQ(qc::make_gate(GateType::X, {0_cbit, 1_cbit}, {3_tbit}), x2);
  EXPECT_EQ(qc::make_gate(X::TYPE_NAME, {0_cbit, 1_cbit}, {3_tbit}), x2);
  auto vt = !v_;
  EXPECT_EQ(qc::make_gate(GateType::V, qc::bedaggered, 0_tbit), vt);
  EXPECT_EQ(qc::make_gate(qc::append_bedaggered_tag(V::TYPE_NAME), 0_tbit), vt);
}

TEST_F(LibraryTest, DecodeAlias) {
  EXPECT_EQ(qc::decode_alias("NOT"), X::TYPE_NAME);
}
