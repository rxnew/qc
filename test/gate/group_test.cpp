#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"
#include "gate/group.hpp"

using namespace qc::literals;
using namespace qc::library;
using qc::Group;
using qc::Gate;

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

TEST_F(GroupTest, Assignment) {
  auto group = Group();
  group = group_;
  EXPECT_EQ(group, group_);
}

TEST_F(GroupTest, GetTypeName) {
  EXPECT_EQ(Group::TYPE_NAME, group_.get_type_name());
}

TEST_F(GroupTest, IsGroup) {
  EXPECT_TRUE(group_.is_group());
}
