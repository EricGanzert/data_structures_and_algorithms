#pragma once

#include <cstdint>
#include <vector>

void findSmallestAndLargest(const std::vector<int>& array, int& smallest, int& largest);

struct Pair {
    int first{};
    double second{};
};

uint64_t sumOfIntsSmaller(uint32_t n);

// returns true if n == mi for some i
bool isMultiple(uint64_t n, uint64_t m);