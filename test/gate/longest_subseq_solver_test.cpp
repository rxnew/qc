#include <vector>
#include <list>
#include <deque>
#include <functional>

#include "gtest/gtest.h"

#include "length_subseq.hpp"

using exam1::LongestSubseqSolver;

class LongestSubseqSolverTest : public ::testing::Test {};

using LongestIncreasingDecimalSubseqSolverTest = LongestSubseqSolverTest;
using LongestEquivalenceBinarySubseqSolverTest = LongestSubseqSolverTest;
using LongestEquivalenceLetterSubseqSolverTest = LongestSubseqSolverTest;

template <class E>
struct TestCase {
  std::vector<E> input;
  std::vector<E> expected;
};

// 要素が数字の列の最長増加部分列
TEST_F(LongestIncreasingDecimalSubseqSolverTest, solve) {
  // テストケース
  const std::vector<TestCase<int>> TEST_CASES = {
    // 先頭の部分列が解
    {{0, 1, 2, 0, 1}, {0, 1, 2}},
    // 最後尾の部分列が解
    {{0, 1, 0, 1, 2}, {0, 1, 2}},
    // 中間の部分列が解
    {{0, 1, 0, 1, 2, 0, 1}, {0, 1, 2}},
    // 入力列と解の部分列が等しい
    {{0, 1}, {0, 1}},
    // 要素0-9に対応
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},
    // 要素数1の列に対応
    {{0}, {0}},
    // 空の列に対応
    {{}, {}},
    // 同じ数字は部分列に含まない
    {{0, 0}, {0}}
  };

  for(const auto& test : TEST_CASES) {
    EXPECT_EQ(LongestSubseqSolver::solve(test.input, std::less<int>()),
              test.expected);
  }
}

// 要素が0, 1の列の最長同値部分列
TEST_F(LongestEquivalenceBinarySubseqSolverTest, solve) {
  // テストケース
  const std::vector<TestCase<int>> TEST_CASES = {
    // 先頭の部分列が解
    {{0, 0, 0, 1, 1}, {0, 0, 0}},
    // 最後尾の部分列が解
    {{0, 0, 1, 1, 1}, {1, 1, 1}},
    // 中間の部分列が解
    {{0, 0, 1, 1, 1, 0, 0}, {1, 1, 1}},
    // 入力列と解の部分列が等しい
    {{0, 0}, {0, 0}},
    // 要素数1の列に対応
    {{0}, {0}},
    // 空の列に対応
    {{}, {}},
  };

  for(const auto& test : TEST_CASES) {
    EXPECT_EQ(LongestSubseqSolver::solve(test.input, std::equal_to<int>()),
              test.expected);
  }
}

// 要素が英字の列の最長同字部分列
TEST_F(LongestEquivalenceLetterSubseqSolverTest, solve) {
  // テストケース
  const std::vector<TestCase<char>> TEST_CASES = {
    // 先頭の部分列が解
    {{'A', 'A', 'A', 'B', 'B'}, {'A', 'A', 'A'}},
    // 最後尾の部分列が解
    {{'A', 'A', 'B', 'B', 'B'}, {'B', 'B', 'B'}},
    // 中間の部分列が解
    {{'A', 'A', 'B', 'B', 'B', 'A', 'A'}, {'B', 'B', 'B'}},
    // 入力列と解の部分列が等しい
    {{'A', 'A'}, {'A', 'A'}},
    // 要素'Z'に対応
    {{'Z', 'Z'}, {'Z', 'Z'}},
    // 要素'a'に対応
    {{'a', 'a'}, {'a', 'a'}},
    // 要素'z'に対応
    {{'z', 'z'}, {'z', 'z'}},
    // 要素数1の列に対応
    {{'A'}, {'A'}},
    // 空の列に対応
    {{}, {}},
    // 大文字と小文字は区別
    {{'A', 'A', 'a'}, {'A', 'A'}},
  };

  for(const auto& test : TEST_CASES) {
    EXPECT_EQ(LongestSubseqSolver::solve(test.input, std::equal_to<char>()),
              test.expected);
  }
}

template <class T>
class LongestSubseqSolverTypedTest : public ::testing::Test {};

using TestTypes = ::testing::Types<std::vector<int>,
                                   std::list<int>,
                                   std::deque<int>>;

TYPED_TEST_CASE(LongestSubseqSolverTypedTest, TestTypes);

// 型付けテスト
TYPED_TEST(LongestSubseqSolverTypedTest, solve) {
  TypeParam input    = {1, 2, 3, 1, 2};
  TypeParam expected = {1, 2, 3};
  EXPECT_EQ(LongestSubseqSolver::solve(input, std::less<int>()),
            expected);
}
