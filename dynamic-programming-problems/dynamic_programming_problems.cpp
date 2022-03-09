#include "dynamic_programming_problems.h"

using namespace std;

int Knapsack::solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    return solveKnapsackBruteForceRecursive(profits, weights, capacity, 0);
}

// first solution: brute force recursive:
//
// for each item 'i'
//   create a new set which includes item 'i' if the total weight does not exceed capacity
//     recursively process the remaining capacity and items
//   create a new set without item 'i' and recursively process the remaining items
// return the set from the above 2 sets with higher profit

int Knapsack::solveKnapsackBruteForceRecursive(const vector<int> &profits, const vector<int> &weights, int capacity, int currentIndex)
{
    if (capacity <= 0 || currentIndex >= profits.size())
    {
        return 0;
    }

    int profit1 = 0;
    if (weights[currentIndex] <= capacity)
    {
        profit1 = profits[currentIndex] + solveKnapsackBruteForceRecursive(profits, weights, capacity - weights[currentIndex], currentIndex + 1);
    }

    int profit2 = solveKnapsackBruteForceRecursive(profits, weights, capacity, currentIndex + 1);
    return max(profit1, profit2);
}
