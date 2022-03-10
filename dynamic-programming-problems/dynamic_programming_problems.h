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