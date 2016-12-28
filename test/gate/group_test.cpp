#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"
#include "gate/group.hpp"

using namespace qc::literals;
using namespace qc::library_gates;
using qc::Group;
using qc::Gate;

class GroupTest : public ::testing::Test {
 protected:
  GroupTest() :
    gates_{Gate::make<X>(0_tbit), Gate::make<S>(1_tbit)},
    group_(gates_) {}

  qc::Gates gates_;
  Group group_;
};

TEST_F(GroupTest, Constructor) {
  EXPECT_EQ(gates_, group_.get_gates());
}

TEST_F(GroupTest, CopyConstructor) {
  Group group(group_);
  EXPECT_EQ(group, group_);
}

TEST_F(GroupTest, Assignment) {
  auto group = Group();
  group = group_;
  EXPECT_EQ(group, group_);
}

TEST_F(GroupTest, IsEqual) {
  EXPECT_EQ(Group(gates_), group_);
  EXPECT_EQ(Group::make(gates_), group_);
}

TEST_F(GroupTest, IsNotEqual) {
  auto gates1 = qc::Gates{Gate::make<X>(1_tbit), Gate::make<S>(1_tbit)};
  auto gates2 = qc::Gates{Gate::make<X>(0_tbit)};
  EXPECT_NE(Group(gates1), group_);
  EXPECT_NE(Group(gates2), group_);
  EXPECT_NE(X(1_tbit), group_);
}

TEST_F(GroupTest, GetTypeName) {
  EXPECT_EQ(Group::TYPE_NAME, group_.get_type_name());
}

TEST_F(GroupTest, IsGroup) {
  EXPECT_TRUE(group_.is_group());
}

TEST_F(GroupTest, Beaggered) {
  EXPECT_FALSE(group_.bedaggered());
}

TEST_F(GroupTest, Invert) {
  auto group = group_;
  group.invert();
  auto gates = qc::Gates{Gate::make<S>(qc::bedaggered, 1_tbit),
                         Gate::make<X>(0_tbit)};
  EXPECT_EQ(Group(gates), group);
}
