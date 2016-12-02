#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"
#include "gate/group.hpp"

using qc::operator"" _bit;
using qc::operator"" _tbit;
using qc::operator"" _cbit;
using qc::X;
using qc::Y;
using qc::Group;
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

TEST_F(XTest, GetTypeName) {
  EXPECT_EQ("X", x_.get_type_name());
}

TEST_F(XTest, IsNotGroup) {
  EXPECT_EQ(false, x_.is_group());
}

class GroupTest : public ::testing::Test {
 protected:
  GroupTest() : group_(Gate::make<X>(0_tbit)) {}

  Group group_;
};

TEST_F(GroupTest, IsEqual) {
  auto const x = X(0_tbit);
  EXPECT_EQ(Group(x), group_);
  EXPECT_EQ(Group::make(x), group_);
}

TEST_F(GroupTest, IsNotEqual) {
  auto const x = X(1_tbit);
  EXPECT_NE(Group(x), group_);
  EXPECT_NE(x, group_);
}

TEST_F(GroupTest, GetTypeName) {
  EXPECT_EQ("Group", group_.get_type_name());
}

TEST_F(GroupTest, IsGroup) {
  EXPECT_EQ(true, group_.is_group());
}
