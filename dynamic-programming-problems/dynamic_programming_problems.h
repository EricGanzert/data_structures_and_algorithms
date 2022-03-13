#pragma once

#include <vector>

class Knapsack {
public:
    int solveKnapsackBruteForceRecursive(const std::vector<int>& profits, const std::vector<int>& weights, int capacity);
    int solveKnapsackMemoizeRecursive(const std::vector<int>& profits, const std::vector<int>& weights, int capacity);
    int solveKnapsackBottomUpDP(const std::vector<int>& profits, const std::vector<int>& weights, int capacity);

private:
    int knapsackBruteForceRecursive(const std::vector<int>& profits, const std::vector<int>& weights, int capacity, int currentIndex);
    int knapsackMemoizeRecursive(std::vector<std::vector<int>>& dp, 
                               const std::vector<int>& profits, 
                               const std::vector<int>& weights, 
                               int capacity, int currentIndex);
};

int coinChangeGFG(std::vector<int>& coinsToUse, int value);

// Given an infinite supply of coin denominations and a total money amount, we are asked to find the total T
// number of distinct ways to make up that amount
//
// Basic solution:
// for each coind denomination d
//   1. create a set that includes d if it does not exceed T. Recursively process all denominations in the set
//   2. create a set that excludes d and recuresively process the remaining denominations
// return the number of above sets that has a sum equal to T 
class CoinChange {
public:
    int solveCountChangeBruteRecursive(const std::vector<int> &denominations, int total);
    int solveCountChangeMemoizeRecursive(const std::vector<int> &denominations, int total);
    int solveCountChangeBottomUpDP(const std::vector<int> &denominations, int total);

private:
    int countChangeBruteRecursive(const std::vector<int> &denominations, int total, int currentIndex);
    int countChangeMemoizeRecursive(std::vector<std::vector<int>>& dp, const std::vector<int> &denominations, int total, int currentIndex);
};

// Given a set of positive numbers, find if we can partition it into two subsets such that the sum of elements in both subsets are equal
// This is equivalent to finding a subset that equals total sum S / 2
//
// Basic solution:
// for each number i
//   1. create a new set containing the item i if it does not exceed S / 2. Recursively process the remaining elements
//   2. create a new set without i and recursively process the remaining elements
// return true if any of the above sets has a sum equal to S / 2. Return false otherwise.
class PartitionSetEqualSums {
public:
    bool solveBruteRecursive(const std::vector<int>& num);
    bool solveMemoizeRecursive(const std::vector<int>& num);
private:
    bool bruteRecursive(const std::vector<int>& num, int sum, int currentIndex);
    bool memoizeRecursive(std::vector<std::vector<int>>& dp, const std::vector<int>& num, int sum, int currentIndex);
};

// Given a set of positive numbers, determine if there is a subset whose sum is equal to a given number S
//
// Basic solution:
// for each number i
//   1. create a new set containing i if it is not more than S and recursively process the remaining elements
//   2. create a new set without i and recursively process the remaining elements
// return true if any of the above sets has a sum equal to S
class SubsetSum {
public:
  bool solveBruteRecursive(const std::vector<int>& num, int sum);
  bool solveMemoizeRecursive(const std::vector<int>& num, int sum);
private:
  bool bruteRecursive(const std::vector<int> &num, int sum, int currentIndex);
  bool memoizeRecursive(std::vector<std::vector<int>>& dp, const std::vector<int>& num, int sum, int currentIndex);
};

// Given a set of positive numbers, partition the set into 2 subsets with a minimum difference between their subset sums
//
// Basic solution:
// for each number i
//   1. add i to set1 and recursively process the remaining elements
//   2. add i to set2 and recursively process the remaining elements
// return the minimum absolute difference of the above two sets
class MinimumSubsetSumDifference {
public:
    int solveBruteRecursive(const std::vector<int>& num);
    int solveMemoizeRecursive(const std::vector<int>& num);
private:
    int bruteRecursive(const std::vector<int>& num, int sum1, int sum2, int currentIndex);
    int memoizeRecursive(std::vector<std::vector<int>>& dp, const std::vector<int>& sum, int sum1, int sum2, int currentIndex);
};

// Given a set of positive numbers, find the total number of subsets whose sum is eual to a given number S
// 
// Basic solution
// for each number i
//   1. create a new set that contains i if it does not exceed S and recursively process the remaining elements
//   2. create a new ser that excludes i and recursively process the remaining elements
// return the total number of sets whose sum equals S
class CountOfSubsetSum {
public:
  int solveBruteRecursive(const std::vector<int>& num, int sum);
private:
  int bruteRecursive(const std::vector<int>& num, int sum, int currentIndex);
};

// given 2 integer arrays to represent the weights and profits of N items, we need to find a subset of items that will give us
// maximum profit such that their cumulative weight it not more than a given number C. We can assume an infinite supply of item quantities, 
// each item can be selected more than once.
//
// Basic solution:
// for each item in i
//   1. create a new subset that includes i if it's weight does not exceed C. Recursively process all items with C = C - weight of i
//   2. create a new subset that does not include i and recursively process the remaining items.
// return the set from the above two sets that has higher profit
class UnboundedKnapsack {
public:
  int solveBruteRecursive(const std::vector<int>& weights, const std::vector<int>& profits, int capacity);
private:
  int bruteRecursive(const std::vector<int>& weights, const std::vector<int>& profits, int capacity, int currentIndex);
};

// Given a rod of length n we are asked to cut the rod and sell the pieces in a way that will maximize the profit.
// We are also given the price of every piece of length i where 1 <= i <= n
//
// Basic Solution
// for each length l
//   1. create a new set that includes length l if it does not exceed the remaining length. Recursively process all lengths
//   2. create a new set that excludes length l and recursively process remaining elements.
// return the set from the above 2 sets that has the highest profit
class RodCutting {
public:
  int solveBruteRecursive(const std::vector<int>& lengths, const std::vector<int>& prices, int totalLength);
private:
  int bruteRecursive(const std::vector<int>& lengths, const std::vector<int>& prices, int remainingLength, int currentIndex);
};