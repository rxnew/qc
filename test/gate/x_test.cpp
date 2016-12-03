#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"

using namespace qc::literals;
using namespace qc::library;
using qc::Gate;

class XTest : public ::testing::Test {
 protected:
  XTest() : x_(0_tbit), xt_(qc::bedaggered, 0_tbit) {}

  X x_;
  X xt_;
};

TEST_F(XTest, Constructor) {
  EXPECT_EQ(qc::CBits{}, x_.get_cbits());
  EXPECT_EQ(qc::TBits{0_tbit}, x_.get_tbits());
}

TEST_F(XTest, CopyConstructor) {
  X x(x_);
  EXPECT_EQ(x, x_);
  X xt(xt_);
  EXPECT_EQ(xt, xt_);
}

TEST_F(XTest, Assignment) {
  auto x = X();
  x = x_;
  EXPECT_EQ(x, x_);
  auto xt = X();
  xt = xt_;
  EXPECT_EQ(xt, xt_);
}

TEST_F(XTest, IsEqual) {
  EXPECT_EQ(x_, xt_);
  EXPECT_EQ(X(0_tbit), x_);
  EXPECT_EQ(Gate::make<X>(0_tbit), x_);
}

TEST_F(XTest, IsNotEqual) {
  EXPECT_NE(X(1_tbit), x_);
  EXPECT_NE(Y(0_tbit), x_);
}

TEST_F(XTest, GetTypeName) {
  EXPECT_EQ(X::TYPE_NAME, x_.get_type_name());
  EXPECT_EQ(X::TYPE_NAME, xt_.get_type_name());
}

TEST_F(XTest, IsNotGroup) {
  EXPECT_FALSE(x_.is_group());
}

TEST_F(XTest, Bedaggered) {
  EXPECT_FALSE(x_.bedaggered());
  EXPECT_FALSE(xt_.bedaggered());
}

TEST_F(XTest, Invert) {
  auto x = x_;
  x.invert();
  EXPECT_EQ(x, x_);
}
