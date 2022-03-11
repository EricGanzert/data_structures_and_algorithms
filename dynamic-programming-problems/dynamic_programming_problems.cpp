#include "dynamic_programming_problems.h"
#include <iostream>

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

// if N = 12 and the coins we can use are {1, 5, 10}
//
// Index of array of coins:
// [0, 1,  2]
// array of coins
// [1, 5, 10]
//
// Index of array of ways:
// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
// Array of ways
// [0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0]
//
// first we can init our array of ways to 1's because if we had n=0 there is one way to fulfill that,
// by using 0 coins
//
// Index of array of ways:
// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
// Array of ways
// [1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0]
//
// now compare each coins[i] value to all of the ways array indexes j.
// if the ith coin is <= the index j then ways[j] = ways[j] + ways[j-coins[i]]
//
// using first coin 1c
// array of ways
// [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
//
// next using second coin 5c
// array of ways
// [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3]
//
// next using third coin 10c
// array of ways
// [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 4]

int coinChangeGFG(vector<int>& coinsToUse, int value)
{
    vector<int> ways(value + 1, 0);
    ways[0] = 1;

    for (int i = 0; i < coinsToUse.size(); i++)
    {
        auto coin = coinsToUse[i];
        for (int j = 0; j < ways.size(); j++)
        {
            if (coin <= j)
            {
                ways[j] = ways[j] + ways[j-coin];
            }
        }

        // print for debugging purposes
        cout << "ways: [";
        for (int j = 0; j < ways.size(); j++)
        {
            cout << ways[j];
            if (j < ways.size() - 1)
            {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }

    return ways[value];
}

// a brute force recursive solution would look like this:
// for each coin in coinsToUse:
//   create a new set which includes one quantity of the coin if it does not exceed value
//     recursively call to process all coins
//   create a new set without the coin and recursively call to process the remaining coins
// return the count of sets who have a sum equal to value

int CoinChange::solveCountChangeBruteRecursive(const vector<int> &denominations, int total)
{
    return countChangeBruteRecursive(denominations, total, 0);
}

int CoinChange::solveCountChangeMemoizeRecursive(const vector<int> &denominations, int total)
{
    vector<vector<int>> dp(denominations.size(), vector<int>(total + 1));
    return countChangeMemoizeRecursive(dp, denominations, total, 0);
}

int CoinChange::countChangeBruteRecursive(const vector<int>& denominations, int total, int currentIndex)
{
    if (total == 0)
    {
        return 1;
    }

    if (denominations.empty() || currentIndex >= static_cast<int>(denominations.size()))
    {
        return 0;
    }

    int sum1 = 0;
    if (denominations[currentIndex] <= total)
    {
        sum1 = countChangeBruteRecursive(denominations, total - denominations[currentIndex], currentIndex);
    }

    int sum2 = countChangeBruteRecursive(denominations, total, currentIndex + 1);
    return sum1 + sum2;
}

// in this version we remember what result we got for each index used and remaining total.
// this result will be valid for any other branch of the problem that arrives at the same index and remaining total
// so it will prevent extra instances of this recursion from continuing to completion which could be a long path taken unnecessarily
//
// for each coin in the denominations
int CoinChange::countChangeMemoizeRecursive(vector<vector<int>>& dp, const vector<int>& denominations, int total, int currentIndex)
{
    if (total == 0)
    {
        return 1;
    }

    if (denominations.empty() || currentIndex >= static_cast<int>(denominations.size()))
    {
        return 0;
    }

    if (dp[currentIndex][total] > 0)
    {
        return dp[currentIndex][total];
    }

    int sum1 = 0;
    if (denominations[currentIndex] <= total)
    {
        sum1 = countChangeMemoizeRecursive(dp, denominations, total - denominations[currentIndex], currentIndex);
    }

    int sum2 = countChangeMemoizeRecursive(dp, denominations, total, currentIndex + 1);
    dp[currentIndex][total] = sum1 + sum2;
    return dp[currentIndex][total];
}

// We will try to find if we can make all possible sums, with every combination of coins
// to populate the array dp[TotalDenominations][Total+1]
//
// So for every possible total t in (0 <= t <= Total) and for every possible coin index in (0 <= index <= totalDenominations)
// we have 2 options:
// 1. Exclude the coin. Count all the coin combinations without the given coin up to the total t => dp[index-1][t]
// 2. Include the coin if it's value is not more than t. In this case  we will count all the coin combinations to get the remaining
// total: dp[index][t - denominations[index]]
// Finally, to find the total combinations we will add both of the above values sum1 + sum2
int CoinChange::solveCountChangeBottomUpDP(const vector<int>& denominations, int total)
{
    int n = static_cast<int>(denominations.size());
    vector<vector<int>> dp(n, vector<int>(total + 1, 0));

    // populate the total=0 columns, as we will always have an empty set for zero total
    for (int i=0; i<n; i++)
    {
        dp[i][0] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int t = 1; t <= total; t++)
        {
            int sum1 = 0;
            if (i > 0) // if there is a result for this total made from previously seen denominations
            {
                sum1 = dp[i-1][t];
            }

            int sum2 = 0;
            if (t >= denominations[i]) // if we have room to use this coin
            {
                sum2 = dp[i][t - denominations[i]];
            }
            dp[i][t] = sum1 + sum2;
        }
    }

    return dp[n-1][total];
}

bool PartitionSetEqualSums::solveBruteRecursive(const vector<int>& num)
{
    if (num.empty())
    {
        return false;
    }

    int sum = 0;
    for (const auto& item : num)
    {
        sum += item;
    }

    if (sum % 2 != 0)
    {
        return false;
    }

    return bruteRecursive(num, sum / 2, 0);
}

bool PartitionSetEqualSums::solveMemoizeRecursive(const vector<int> &num)
{
    if (num.empty())
    {
        return false;
    }

    int sum = 0;
    for (int i=0; i < static_cast<int>(num.size()); i++)
    {
        sum += num[i];
    }

    if (sum % 2 != 0)
    {
        return false;
    }

    vector<vector<int>> dp(num.size(), vector<int>((sum / 2) + 1, -1));
    return memoizeRecursive(dp, num, sum / 2, 0);
}

bool PartitionSetEqualSums::bruteRecursive(const vector<int>& num, int sum, int currentIndex)
{
    if (sum == 0)
    {
        return true;
    }

    if (num.empty() || currentIndex >= static_cast<int>(num.size()))
    {
        return false;
    }

    if (num[currentIndex] <= sum)
    {
        if (bruteRecursive(num, sum - num[currentIndex], currentIndex + 1))
        {
            return true;
        }
    }

    return bruteRecursive(num, sum, currentIndex + 1);
}

bool PartitionSetEqualSums::memoizeRecursive(vector<vector<int>>& dp, const vector<int>& num, int sum, int currentIndex)
{
    if (sum == 0)
    {
        return true;
    }

    if (currentIndex >= static_cast<int>(num.size()))
    {
        return false;
    }

    if (dp[currentIndex][sum] != -1)
    {
        return dp[currentIndex][sum];
    }

    bool path1 = false;
    if (num[currentIndex] <= sum)
    {
        if (path1 = memoizeRecursive(dp, num, sum - num[currentIndex], currentIndex + 1))
        {
            dp[currentIndex][sum] = int{true};
            return dp[currentIndex][sum];
        }
    }

    bool path2 = memoizeRecursive(dp, num, sum, currentIndex + 1);
    dp[currentIndex][sum] = int{path1 || path2};
    return dp[currentIndex][sum]; 
}

bool SubsetSum::solveBruteRecursive(const vector<int> &num, int sum)
{
    return bruteRecursive(num, sum, 0);
}

bool SubsetSum::bruteRecursive(const vector<int> &num, int sum, int currentIndex)
{
    if (currentIndex >= static_cast<int>(num.size()))
    {
        return false;
    }

    if (sum == 0)
    {
        return true;
    }

    if (num[currentIndex] <= sum)
    {
        if (bruteRecursive(num, sum - num[currentIndex], currentIndex + 1))
        {
            return true;
        }
    }

    return bruteRecursive(num, sum, currentIndex + 1);
}

int MinimumSubsetSumDifference::solveBruteRecursive(const vector<int>& num)
{
    return bruteRecursive(num, 0, 0, 0);
}

int MinimumSubsetSumDifference::bruteRecursive(const vector<int>& num, int sum1, int sum2, int currentIndex)
{
    if (currentIndex >= static_cast<int>(num.size()))
    {
        return abs(sum1 - sum2);
    }

    int diff1 = bruteRecursive(num, sum1 + num[currentIndex], sum2, currentIndex + 1);
    int diff2 = bruteRecursive(num, sum1, sum2 + num[currentIndex], currentIndex + 1);

    return min(diff1, diff2);
}

int CountOfSubsetSum::solveBruteRecursive(const vector<int>& num, int sum)
{
    return bruteRecursive(num, sum, 0);
}

int CountOfSubsetSum::bruteRecursive(const vector<int>& num, int sum, int currentIndex)
{
    if (sum == 0)
    {
        return 1;
    }

    if (currentIndex >= static_cast<int>(num.size()))
    {
        return 0;
    }

    int count1 = 0;
    if (num[currentIndex] <= sum)
    {
        count1 = bruteRecursive(num, sum - num[currentIndex], currentIndex + 1);
    }

    int count2 = bruteRecursive(num, sum, currentIndex + 1);
    return count1 + count2;
}

int UnboundedKnapsack::solveBruteRecursive(const vector<int>& weights, const vector<int>& profits, int capacity)
{
    return bruteRecursive(weights, profits, capacity, 0);
}

int UnboundedKnapsack::bruteRecursive(const vector<int>& weights, const vector<int>& profits, int capacity, int currentIndex)
{
    if (currentIndex >= static_cast<int>(weights.size()) || capacity <= 0)
    {
        return 0;
    }

    int profit1 = 0;
    if (weights[currentIndex] <= capacity)
    {
        profit1 = profits[currentIndex] + bruteRecursive(weights, profits, capacity - weights[currentIndex], currentIndex);
    }

    int profit2 = bruteRecursive(weights, profits, capacity, currentIndex + 1);
    return max(profit1, profit2);
}

int RodCutting::solveBruteRecursive(const vector<int>& lengths, const vector<int>& prices, int totalLength)
{
    return bruteRecursive(lengths, prices, totalLength, 0);
}

int RodCutting::bruteRecursive(const vector<int>& lengths, const vector<int>& prices, int remainingLength, int currentIndex)
{
    if (currentIndex >= static_cast<int>(lengths.size()) || remainingLength <= 0)
    {
        return 0;
    }

    int profit1 = 0;
    if (lengths[currentIndex] <= remainingLength)
    {
        profit1 = prices[currentIndex] + bruteRecursive(lengths, prices, remainingLength - lengths[currentIndex], currentIndex);
    }

    int profit2 = bruteRecursive(lengths, prices, remainingLength, currentIndex + 1);
    return max(profit1, profit2);
}