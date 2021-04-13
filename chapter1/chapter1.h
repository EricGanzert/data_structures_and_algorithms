#pragma once

#include <cstdint>
#include <string>
#include <vector>

void findSmallestAndLargest(const std::vector<int>& array, int& smallest, int& largest);

struct Pair {
    int first{};
    double second{};
};

uint64_t sumOfIntsSmaller(uint32_t n);

// returns true if n == mi for some i
bool isMultiple(uint64_t n, uint64_t m);

void printArray(int** A, int m, int n);

class Flower {
public:
    Flower(std::string name, int numPedals, float price);

    std::string getName();
    void setName(std::string name);

    int getNumPedals();
    void setNumPedals(int numPedals);

    float getPrice();
    void setPrice(float price);

private:
    std::string m_name{};
    int m_numPedals{};
    float m_price{};
};