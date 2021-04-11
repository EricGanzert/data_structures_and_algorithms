#include "chapter1.h"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace testing;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(FindSmallestAndLargestTest, FindsSmallestAndLargest)
{
    vector<int> sampleArray = {6, -1, -2, 3, 4, 5};
    int smallest{};
    int largest{};

    findSmallestAndLargest(sampleArray, smallest, largest);

    EXPECT_EQ(smallest, -2);
    EXPECT_EQ(largest, 6);
}

TEST(FindSmallestAndLargestTest, DoesntThrowIfEmpty)
{
    int smallest{};
    int largest{};

    vector<int> emptyVector{};
    ASSERT_NO_THROW(findSmallestAndLargest(emptyVector, smallest, largest));
}

TEST(FindSmallestAndLargestTest, OnlyOneInVector)
{
    int smallest{};
    int largest{};

    smallest = 0;
    largest = 0;

    vector<int> hasOne {-1};

    findSmallestAndLargest(hasOne, smallest, largest);
    EXPECT_EQ(smallest, -1);
    EXPECT_EQ(smallest, -1);
}
