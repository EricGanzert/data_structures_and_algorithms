#include "chapter1.h"

#include <iostream>

using namespace std;

void findSmallestAndLargest(const vector<int>& array, int& smallest, int& largest)
{
    if (array.empty())
    {
        return;
    }

    smallest = array.front();
    largest = array.front();

    for (auto item : array)
    {
        if (item < smallest)
        {
            smallest = item;
        }
        if (item > largest)
        {
            largest = item;
        }
    }
}

uint64_t sumOfIntsSmaller(uint32_t n)
{
    return ((uint64_t{n}-1)*uint64_t{n})/2;
}

bool isMultiple(uint64_t n, uint64_t m)
{
    // returns true if n == mi for some integer i
    if (n == 0)
    {
        return true;
    }

    if (m == 0)
    {
        return n==m;
    }

    if (n < m && n != 0)
    {
        return false;
    }

    auto i = n / m;
    return m == n / i;
}

void printArray(int** A, int m, int n)
{
    if (m < 1 || n < 1)
    {
        return;
    }
    
    for (int rowIndex = 0; rowIndex < m; ++rowIndex)
    {
        auto row = *(A + rowIndex);
        for (int index = 0; index < n; ++index)
        {
            cout << row[index] << " ";
        }
        cout << endl;
    }
}