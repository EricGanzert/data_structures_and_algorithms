#pragma once

#include <vector>

class Knapsack {
public:
  int solveKnapsack(const std::vector<int>& profits, const std::vector<int>& weights, int capacity);
private:
  int solveKnapsackBruteForceRecursive(const std::vector<int>& profits, const std::vector<int>& weights, int capacity, int currentIndex);
};