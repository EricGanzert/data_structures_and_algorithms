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

class CoinChange {
public:
  int solveCountChangeBruteRecursive(const std::vector<int> &denominations, int total);
  int solveCountChangeMemoizeRecursive(const std::vector<int> &denominations, int total);
  int solveCountChangeBottomUpDP(const std::vector<int> &denominations, int total);

private:
  int countChangeBruteRecursive(const std::vector<int> &denominations, int total, int currentIndex);
  int countChangeMemoizeRecursive(std::vector<std::vector<int>>& dp, const std::vector<int> &denominations, int total, int currentIndex);
};

class PartitionSetEqualSums {
public:
  bool solveBruteRecursive(const std::vector<int>& num);
private:
  bool bruteRecursive(const std::vector<int>& num, int sum, int currentIndex);
};

class SubsetSum {
public:
  bool solveBruteRecursive(const std::vector<int> &num, int sum);
private:
  bool bruteRecursive(const std::vector<int> &num, int sum, int currentIndex);
};

class MinimumSubsetSumDifference {
public:
    int solveBruteRecursive(const std::vector<int>& num);
private:
    int bruteRecursive(const std::vector<int>& num, int sum1, int sum2, int currentIndex);
};

class CountOfSubsetSum {
public:
  int solveBruteRecursive(const std::vector<int>& num, int sum);
private:
  int bruteRecursive(const std::vector<int>& num, int sum, int currentIndex);
};

class UnboundedKnapsack {
public:
  int solveBruteRecursive(const std::vector<int>& weights, const std::vector<int>& profits, int capacity);
private:
  int bruteRecursive(const std::vector<int>& weights, const std::vector<int>& profits, int capacity, int currentIndex);
};