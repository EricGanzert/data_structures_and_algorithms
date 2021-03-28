#include <iostream>
#include <vector>
#include "gtest/gtest.h"

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CH1Test, basic)
{
    bool allClear = true;

    // R-1.2
    // find largest and smallest numbers in an array of numbers
    vector<int> sampleArray = {6, -1, -2, 3, 4, 5};
    int smallest{};
    int largest{};

    findSmallestAndLargest(sampleArray, smallest, largest);
    if (smallest != -2 || largest != 6)
    {
        allClear = false;
        cout << "FAIL" << endl;
    }

    // make sure it doesn't throw on an empty array
    vector<int> emptyOne{};
    try 
    {
        findSmallestAndLargest(emptyOne, smallest, largest);
    } catch (...)
    {
        allClear = false;
        cout << "FAIL" << endl;
    }

    // make sure both are set to the one element of a single element array
    smallest = 0;
    largest = 0;
    vector<int> hasOne {-1};

    findSmallestAndLargest(hasOne, smallest, largest);

    if (smallest != -1 || largest != -1)
    {
        allClear = false;
        cout << "FAIL" << endl;
    }

    // test out clang format
    char varOne; char varTwo;
    (void)varOne;
    (void)varTwo;

    EXPECT_TRUE(allClear);
}