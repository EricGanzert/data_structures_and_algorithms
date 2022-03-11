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