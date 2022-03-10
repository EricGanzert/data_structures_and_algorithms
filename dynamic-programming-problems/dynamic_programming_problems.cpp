#include "dynamic_programming_problems.h"

using namespace std;

int Knapsack::solveKnapsackBruteForceRecursive(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    return knapsackBruteForceRecursive(profits, weights, capacity, 0);
}

// first solution: brute force recursive:
//
// for each item 'i'
//   create a new set which includes item 'i' if the total weight does not exceed capacity
//     recursively process the remaining capacity and items
//   create a new set without item 'i' and recursively process the remaining items
// return the set from the above 2 sets with higher profit

int Knapsack::knapsackBruteForceRecursive(const vector<int> &profits, const vector<int> &weights, int capacity, int currentIndex)
{
    if (capacity <= 0 || currentIndex >= profits.size())
    {
        return 0;
    }

    int profit1 = 0;
    if (weights[currentIndex] <= capacity)
    {
        profit1 = profits[currentIndex] + knapsackBruteForceRecursive(profits, weights, capacity - weights[currentIndex], currentIndex + 1);
    }

    int profit2 = knapsackBruteForceRecursive(profits, weights, capacity, currentIndex + 1);
    return max(profit1, profit2);
}

// second solution: use memoization with recursion
// there are overlapping sub problems in the brute force approach where different combinations of selected items
// can cause the same index and capactity to be present in different branches of the problem. So if we arrive at
// 2 different nodes with the same starting index and capacity the answer will be the same. Because the remaining elements
// are the same in both cases and no matter what choices we made perviously we ended up with the same remaining capactiy.
// the profits accumulated up to that point may be different in this situation but what we care about is how much profit is remaining
// in the unchecked items. That is what's being compared for 2 different paths and optimized.
// 
// So we make a 2D array to hold answers we have found for every currentIndex and capacity. For every currentIndex there may be
// many capacities depending on the branch that is taken. The number of rows is profits.size() because that's how many indexes there are in total.
// the number of columns is total capacity + 1 because the remaining capacity may be zero up to and inclusing the initial total capacity.
// Every time we find an answer we save it. This includes considering which subtree is higher as the max of profit1, profit2.
// Simply save our result in the table before returing the answer.

int Knapsack::solveKnapsackMemoizeRecursive(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    vector<vector<int>> dp(profits.size(), vector<int>(capacity + 1, -1));
    return knapsackMemoizeRecursive(dp, profits, weights, capacity, 0);
}

int Knapsack::knapsackMemoizeRecursive(vector<vector<int>>& dp, const vector<int>& profits, 
                                    const vector<int>& weights, int capacity, int currentIndex)
{
    if (capacity <= 0 || currentIndex >= profits.size())
    {
        return 0;
    }

    if (dp[currentIndex][capacity] != -1)
    {
        return dp[currentIndex][capacity];
    }

    int profit1 = 0;
    if (weights[currentIndex] <= capacity)
    {
        profit1 = profits[currentIndex] + knapsackMemoizeRecursive(dp, profits, weights, capacity - weights[currentIndex], currentIndex + 1);
    }

    int profit2 = knapsackMemoizeRecursive(dp, profits, weights, capacity, currentIndex + 1);

    dp[currentIndex][capacity] = max(profit1, profit2);
    return dp[currentIndex][capacity];
}

// third solution: bottom up dynamic programming
// Let's try to populate our dp[][] array from the bottom up. Essentially, we want to find the maximum profit for every sub-array and for every
// possible capacity. This means dp[i][c] will represent the maximum knapsack profit for capacity 'c' calculated from the first i items.
// 
// So for each item at index i (0 <= i < items.length) and capacity c (0 <= c <= capacity), we have two options:
// 1. Exclude the item at index i. In this case we will take whatever profit we get from the sub-array excluding this item dp[i-1][c]
// 
// 2. Include the item at index i if it's weight is not more than the capacity. In this case we include it's profit plus whatever profit we 
// get from the remaining capacity and remaining items profits[i] + dp[i-1][c - weights[i]]
//
// Finally our optimal solution will be the maximum of the two above values
// dp[i][c] = max(dp[i-1][c], profits[i] + dp[i-1][c - weights[i]])
// the base case is zero capacity

int Knapsack::solveKnapsackBottomUpDP(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    if (capacity <= 0 || profits.empty() || weights.size() != profits.size())
    {
        return 0;
    }

    auto n = static_cast<int>(profits.size());
    vector<vector<int>> dp(n, vector<int>(capacity + 1));

    // populate the capacity=0 columns, with 0 capacity we have 0 profit
    for (int i=0; i<n; i++)
    {
        dp[i][0] = 0;
    }

    // if we only have 1 item we will take it if it's not more than our capacity
    for (int c = 0; c <= capacity; c++)
    {
        if (weights[0] <= c)
        {
            dp[0][c] = profits[0];
        }
    }

    // process all sub-arrays for all the capacities
    for (int i = 1; i < n; i++)
    {
        for (int c = 1; c <= capacity; c++)
        {
            int profit1 = 0;
            int profit2 = 0;

            if (weights[i] <= c)
            {
                profit1 = profits[i] + dp[i-1][c - weights[i]];
            }

            profit2 = dp[i-1][c];

            dp[i][c] = max(profit1, profit2);
        }
    }

    return dp[n-1][capacity];
}