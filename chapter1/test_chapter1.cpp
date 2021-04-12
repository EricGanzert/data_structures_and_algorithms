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

// R-1.2
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

    vector<int> hasOne {-1};

    findSmallestAndLargest(hasOne, smallest, largest);
    EXPECT_EQ(smallest, -1);
    EXPECT_EQ(smallest, -1);
}

// R-1.3
TEST(PairStructTest, InitToZero)
{
    Pair p;
    EXPECT_EQ(p.first, 0);
    EXPECT_EQ(p.second, 0.0);
}

// R-1.4
TEST(StringContents, CheckResult)
{
    string s = "abc";
    string t = "cde";

    s += s + t[1] + s;

    EXPECT_EQ(s, "abcabcdabc");
}


// R-1.5
TEST(OperatorPrecedence, OperatorPrecedence)
{
    double y = 3;
    double z = 4;
    double w = 5;

    auto result = y + 2 * z ++ < 3 - w / 5;
    auto resultWithParen = (y + (2 * (z ++))) < (3 - (w / 5));

    EXPECT_EQ(result, resultWithParen);
}

// R-1.6
TEST(AllocateArray, ProperStorage)
{
    double* dp[10];
    for (auto& i : dp)
    {
        i = new double{0.0};
    }

    for (auto i : dp)
    {
        EXPECT_EQ(*i, 0.0);
    }
}

// R-1.7
TEST(SumOfIntsSmaller, SimpleMathCheck)
{
    auto n = 4u;
    auto expectedResult = 1ul + 2ul + 3ul;

    EXPECT_EQ(sumOfIntsSmaller(n), expectedResult);
}

TEST(SumOfIntsSmaller, MaxArgResultGreater)
{
    auto n = std::numeric_limits<uint32_t>::max();
    auto result = sumOfIntsSmaller(n);
    EXPECT_GT(result, n);
}

// R-1.8
TEST(IsMultiple, IsMultiple)
{
    EXPECT_TRUE(isMultiple(20, 5));
    EXPECT_TRUE(isMultiple(2, 1));
    EXPECT_TRUE(isMultiple(6, 2));
    EXPECT_TRUE(isMultiple(18, 3));
    EXPECT_TRUE(isMultiple(66, 11));

    EXPECT_FALSE(isMultiple(15, 10));
    EXPECT_FALSE(isMultiple(5, 4));
    EXPECT_FALSE(isMultiple(5, 10));
}

TEST(IsMultiple, EdgeCases)
{
    EXPECT_NO_THROW(EXPECT_TRUE(isMultiple(0, 0)));
    EXPECT_NO_THROW(EXPECT_TRUE(isMultiple(0, 10)));
    EXPECT_NO_THROW(EXPECT_FALSE(isMultiple(7, 0)));
}

// R-1.9
TEST(PrintArray, PrintArray)
{
    int** A = nullptr;
    constexpr auto m = 4;
    constexpr auto n = 6;

    A = new int*[m];
    for(auto row=0; row < m; ++row)
    {
        *(A + row) = new int[n];
        auto rowPtr = *(A + row);
        for (auto index=0; index<n; ++index)
        {
            rowPtr[index] = (row * n) + index;
        }
    }

    printArray(A, m, n);
}