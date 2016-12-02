#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"

using qc::operator"" _bit;
using qc::operator"" _tbit;
using qc::operator"" _cbit;
using qc::X;
using qc::Y;
using qc::Gate;

class XTest : public ::testing::Test {
 protected:
  XTest() : x_(0_tbit) {}

  X x_;
};

TEST_F(XTest, IsEqual) {
  EXPECT_EQ(X(0_tbit), x_);
  EXPECT_EQ(Gate::make<X>(0_tbit), x_);
}

TEST_F(XTest, IsNotEqual) {
  EXPECT_NE(X(1_tbit), x_);
  EXPECT_NE(Y(0_tbit), x_);
}

TEST_F(XTest, Assignment) {
  auto x = X();
  x = x_;
  EXPECT_EQ(x, x_);
}

TEST_F(XTest, GetTypeName) {
  EXPECT_EQ("X", x_.get_type_name());
}

TEST_F(XTest, IsNotGroup) {
  EXPECT_EQ(false, x_.is_group());
}
