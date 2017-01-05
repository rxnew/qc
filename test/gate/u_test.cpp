#include "gtest/gtest.h"

#include "gate.hpp"
#include "gate/library.hpp"

using namespace qc::literals;
using namespace qc::library_gates;
using qc::Gate;

auto type_name = "Shor";

class UTest : public ::testing::Test {
 protected:
  UTest() : u_(type_name, 0_tbit), ut_(type_name, qc::bedaggered, 0_tbit) {}

  U u_;
  U ut_;
};

TEST_F(UTest, Constructor) {
  EXPECT_EQ(qc::CBits{}, u_.get_cbits());
  EXPECT_EQ(qc::TBits{0_tbit}, u_.get_tbits());
}

TEST_F(UTest, CopyConstructor) {
  U u(u_);
  EXPECT_EQ(u, u_);
  U ut(ut_);
  std::cout << ut.bedaggered() << std::endl;
  std::cout << ut_.bedaggered() << std::endl;
  EXPECT_EQ(ut, ut_);
}

TEST_F(UTest, Assignment) {
  auto u = U();
  u = u_;
  EXPECT_EQ(u, u_);
  auto ut = U();
  ut = ut_;
  EXPECT_EQ(ut, ut_);
}

TEST_F(UTest, IsEqual) {
  EXPECT_EQ(U(type_name, 0_tbit), u_);
  EXPECT_EQ(U(type_name, qc::bedaggered, 0_tbit), ut_);
  EXPECT_EQ(Gate::make<U>(type_name, 0_tbit), u_);
  EXPECT_EQ(Gate::make<U>(type_name, qc::bedaggered, 0_tbit), ut_);
}

TEST_F(UTest, IsNotEqual) {
  EXPECT_NE(u_, ut_);
  EXPECT_NE(U(type_name, 1_tbit), u_);
  EXPECT_NE(U("Grover", 0_tbit), u_);
  EXPECT_NE(Y(0_tbit), u_);
}

TEST_F(UTest, GetTypeName) {
  EXPECT_EQ(type_name, u_.get_type_name());
  EXPECT_EQ(qc::append_bedaggered_tag(type_name), ut_.get_type_name());
}

TEST_F(UTest, IsNotGroup) {
  EXPECT_FALSE(u_.is_group());
}

TEST_F(UTest, Bedaggered) {
  EXPECT_FALSE(u_.bedaggered());
  EXPECT_TRUE(ut_.bedaggered());
}

TEST_F(UTest, Invert) {
  auto u = u_;
  u.invert();
  EXPECT_TRUE(u.bedaggered());
}
