#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"

using namespace qc::literals;
using namespace qc::library;
using qc::Gate;

class VTest : public ::testing::Test {
 protected:
  VTest() : v_(0_tbit), vt_(qc::bedaggered, 0_tbit) {}

  V v_;
  V vt_;
};

TEST_F(VTest, Constructor) {
  EXPECT_EQ(qc::CBits{}, v_.get_cbits());
  EXPECT_EQ(qc::TBits{0_tbit}, v_.get_tbits());
}

TEST_F(VTest, CopyConstructor) {
  V v(v_);
  EXPECT_EQ(v, v_);
  V vt(vt_);
  EXPECT_EQ(vt, vt_);
}

TEST_F(VTest, Assignment) {
  auto v = V();
  v = v_;
  EXPECT_EQ(v, v_);
  auto vt = V();
  vt = vt_;
  EXPECT_EQ(vt, vt_);
}

TEST_F(VTest, IsEqual) {
  EXPECT_EQ(V(0_tbit), v_);
  EXPECT_EQ(V(qc::bedaggered, 0_tbit), vt_);
  EXPECT_EQ(Gate::make<V>(0_tbit), v_);
  EXPECT_EQ(Gate::make<V>(qc::bedaggered, 0_tbit), vt_);
}

TEST_F(VTest, IsNotEqual) {
  EXPECT_NE(v_, vt_);
  EXPECT_NE(V(1_tbit), v_);
  EXPECT_NE(Y(0_tbit), v_);
}

TEST_F(VTest, GetTypeName) {
  EXPECT_EQ(V::TYPE_NAME, v_.get_type_name());
  EXPECT_EQ(qc::append_bedaggered_tag(V::TYPE_NAME), vt_.get_type_name());
}

TEST_F(VTest, IsNotGroup) {
  EXPECT_FALSE(v_.is_group());
}

TEST_F(VTest, Bedaggered) {
  EXPECT_FALSE(v_.bedaggered());
  EXPECT_TRUE(vt_.bedaggered());
}

TEST_F(VTest, Invert) {
  auto v = v_;
  v.invert();
  EXPECT_EQ(v, vt_);
}
