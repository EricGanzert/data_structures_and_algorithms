#include "chapter1.h"

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