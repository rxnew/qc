#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"

using namespace qc::literals;
using namespace qc::library;
using qc::Gate;
using qc::GateType;

class GateTest : public ::testing::Test {
 protected:
  GateTest() : x_(X(0_tbit)) {}

  Gate x_;
};

TEST_F(GateTest, Constructor) {
  EXPECT_EQ(GateType::X, x_.get_type());
  EXPECT_EQ(qc::CBits{}, x_.get_cbits());
  EXPECT_EQ(qc::TBits{0_tbit}, x_.get_tbits());
}

TEST_F(GateTest, Make) {
  EXPECT_EQ(Gate::make<X>(0_tbit), x_);
  auto x1 = Gate(X(0_cbit, 1_tbit));
  EXPECT_EQ(Gate::make<X>(0_cbit, 1_tbit), x1);
  auto x2 = Gate(X{{0_cbit, 1_cbit}, {3_tbit, 4_tbit}});
  EXPECT_EQ(Gate::make<X>({0_cbit, 1_cbit}, {3_tbit, 4_tbit}), x2);
}

TEST_F(GateTest, CopyConstructor) {
  Gate x(x_);
  EXPECT_EQ(x, x_);
}

TEST_F(GateTest, Assignment) {
  auto x = Gate::make<X>();
  x = x_;
  EXPECT_EQ(x, x_);
  auto y = Gate::make<Y>();
  y = x_;
  EXPECT_EQ(y, x_);
}

TEST_F(GateTest, IsEqual) {
  EXPECT_EQ(Gate(X(0_tbit)), x_);
  EXPECT_EQ(X(0_tbit), x_);
}

TEST_F(GateTest, IsNotEqual) {
  EXPECT_NE(X(1_tbit), x_);
  EXPECT_NE(X(1_cbit, 0_tbit), x_);
  EXPECT_NE(Y(0_tbit), x_);
}
