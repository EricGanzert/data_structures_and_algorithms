#include "dynamic_programming_problems.h"

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(KnapsackTest, BruteForceRecursive)
{
    Knapsack ks;
    vector<int> profits = {1, 6, 10, 16};
    vector<int> weights = {1, 2, 3, 5};
    int maxProfit = ks.solveKnapsackBruteForceRecursive(profits, weights, 7);
    cout << "Total knapsack profit ---> " << maxProfit << endl;
    maxProfit = ks.solveKnapsackBruteForceRecursive(profits, weights, 6);
    cout << "Total knapsack profit ---> " << maxProfit << endl;
}

TEST(KnapsackTest, MemoizeRecursive)
{
    Knapsack ks;
    vector<int> profits = {1, 6, 10, 16};
    vector<int> weights = {1, 2, 3, 5};
    int maxProfit = ks.solveKnapsackMemoizeRecursive(profits, weights, 7);
    cout << "Total knapsack profit ---> " << maxProfit << endl;
    maxProfit = ks.solveKnapsackMemoizeRecursive(profits, weights, 6);
    cout << "Total knapsack profit ---> " << maxProfit << endl;
}

TEST(KnapsackTest, BottomUpDP)
{
    Knapsack ks;
    vector<int> profits = {1, 6, 10, 16};
    vector<int> weights = {1, 2, 3, 5};
    int maxProfit = ks.solveKnapsackBottomUpDP(profits, weights, 7);
    cout << "Total knapsack profit ---> " << maxProfit << endl;
    maxProfit = ks.solveKnapsackBottomUpDP(profits, weights, 6);
    cout << "Total knapsack profit ---> " << maxProfit << endl;
}

TEST(CoinProblem, CoinProblemGFG)
{
    vector<int> coinsToUse = {1, 5, 10};
    int value = 22;

    auto numWays = coinChangeGFG(coinsToUse, value);
}

TEST(PartitionSetEqualTest, BruteForceRecursive)
{
  PartitionSetEqualSums ps;
  vector<int> num = {1, 2, 3, 4};
  EXPECT_THAT(ps.solveBruteRecursive(num), true);
  num = vector<int>{1, 1, 3, 4, 7};
  EXPECT_THAT(ps.solveBruteRecursive(num), true);
  num = vector<int>{2, 3, 4, 6};
  EXPECT_THAT(ps.solveBruteRecursive(num), false);
}

TEST(PartitionSetEqualTest, MemoizeRecursive)
{
  PartitionSetEqualSums ps;
  vector<int> num = {1, 2, 3, 4};
  EXPECT_THAT(ps.solveMemoizeRecursive(num), true);
  num = vector<int>{1, 1, 3, 4, 7};
  EXPECT_THAT(ps.solveMemoizeRecursive(num), true);
  num = vector<int>{2, 3, 4, 6};
  EXPECT_THAT(ps.solveMemoizeRecursive(num), false);
}

TEST(SubsetSumTest, BruteForceRecursive)
{
  SubsetSum ss;
  vector<int> num = {1, 2, 3, 7};
  EXPECT_THAT(ss.solveBruteRecursive(num, 6), true);
  num = vector<int>{1, 2, 7, 1, 5};
  EXPECT_THAT(ss.solveBruteRecursive(num, 10), true);
  num = vector<int>{1, 3, 4, 8};
  EXPECT_THAT(ss.solveBruteRecursive(num, 6), false);
}

TEST(SubsetSumTest, MemoizeRecursive)
{
  SubsetSum ss;
  vector<int> num = {1, 2, 3, 7};
  EXPECT_THAT(ss.solveMemoizeRecursive(num, 6), true);
  num = vector<int>{1, 2, 7, 1, 5};
  EXPECT_THAT(ss.solveMemoizeRecursive(num, 10), true);
  num = vector<int>{1, 3, 4, 8};
  EXPECT_THAT(ss.solveMemoizeRecursive(num, 6), false);
}

TEST(MinSubsetSumDiffTest, BruteForceRecursive)
{
  MinimumSubsetSumDifference mssd;
  vector<int> num = {1, 2, 3, 9};
  EXPECT_THAT(mssd.solveBruteRecursive(num), 3);
  num = vector<int>{1, 2, 7, 1, 5};
  EXPECT_THAT(mssd.solveBruteRecursive(num), 0);
  num = vector<int>{1, 3, 100, 4};
  EXPECT_THAT(mssd.solveBruteRecursive(num), 92);
}

TEST(MinSubsetSumDiffTest, MemoizeRecursive)
{
  MinimumSubsetSumDifference mssd;
  vector<int> num = {1, 2, 3, 9};
  EXPECT_THAT(mssd.solveMemoizeRecursive(num), 3);
  num = vector<int>{1, 2, 7, 1, 5};
  EXPECT_THAT(mssd.solveMemoizeRecursive(num), 0);
  num = vector<int>{1, 3, 100, 4};
  EXPECT_THAT(mssd.solveMemoizeRecursive(num), 92);
}

TEST(CountSubsetSumTest, BruteForceRecursive)
{
  CountOfSubsetSum css;
  vector<int> num = {1, 1, 2, 3};
  EXPECT_THAT(css.solveBruteRecursive(num, 4), 3);
  num = vector<int>{1, 2, 7, 1, 5};
  EXPECT_THAT(css.solveBruteRecursive(num, 9), 3);
}

TEST(CountSubsetSumTest, MemoizeRecursive)
{
  CountOfSubsetSum css;
  vector<int> num = {1, 1, 2, 3};
  EXPECT_THAT(css.solveMemoizeRecursive(num, 4), 3);
  num = vector<int>{1, 2, 7, 1, 5};
  EXPECT_THAT(css.solveMemoizeRecursive(num, 9), 3);
}

TEST(UnboundedKnapsackTest, BruteForceRecursive)
{
  UnboundedKnapsack uks;
  vector<int> profits = {15, 50, 60, 90};
  vector<int> weights = {1, 3, 4, 5};

  EXPECT_THAT(uks.solveBruteRecursive(weights, profits, 8), 140);
  EXPECT_THAT(uks.solveBruteRecursive(weights, profits, 6), 105);
}

TEST(UnboundedKnapsackTest, MemoizeRecursive)
{
  UnboundedKnapsack uks;
  vector<int> profits = {15, 50, 60, 90};
  vector<int> weights = {1, 3, 4, 5};

  EXPECT_THAT(uks.solveMemoizeRecursive(weights, profits, 8), 140);
  EXPECT_THAT(uks.solveMemoizeRecursive(weights, profits, 6), 105);
}

TEST(RodCuttingTest, BruteForceRecursive)
{
  RodCutting rodCut;
  vector<int> lengths = {1, 2, 3, 4, 5};
  vector<int> prices = {2, 6, 7, 10, 13};
  int maxProfit = rodCut.solveBruteRecursive(lengths, prices, 5);
  EXPECT_THAT(maxProfit, 14);
}

TEST(RodCuttingTest, MemoizeRecursive)
{
  RodCutting rodCut;
  vector<int> lengths = {1, 2, 3, 4, 5};
  vector<int> prices = {2, 6, 7, 10, 13};
  int maxProfit = rodCut.solveMemoizeRecursive(lengths, prices, 5);
  EXPECT_THAT(maxProfit, 14);
}

TEST(CoinProblem, CoinProblemBruteRecursive)
{
    vector<int> coinsToUse = {1, 5, 10};
    int value = 22;

    CoinChange cc;
    auto numWays = cc.solveCountChangeBruteRecursive(coinsToUse, value);
    EXPECT_THAT(numWays, 9);
}

TEST(CoinProblem, CoinProblemMemoizeRecursive)
{
    vector<int> coinsToUse = {1, 5, 10};
    int value = 22;

    CoinChange cc;
    auto numWays = cc.solveCountChangeMemoizeRecursive(coinsToUse, value);
    EXPECT_THAT(numWays, 9);
}

TEST(CoinProblem, CoinProblemBottomUpDP)
{
    vector<int> coinsToUse = {1, 5, 10};
    int value = 22;

    CoinChange cc;
    auto numWays = cc.solveCountChangeBottomUpDP(coinsToUse, value);
    EXPECT_THAT(numWays, 9);
}