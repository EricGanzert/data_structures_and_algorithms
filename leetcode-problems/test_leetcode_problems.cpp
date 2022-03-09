#include "leetcode_problems.h"

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TwoSum, TwoSum)
{
    vector<int> input = {2, 7, 11, 15};

    auto result = twoSum(input, 9);

    EXPECT_THAT(count(result.begin(), result.end(), 0), 1);
    EXPECT_THAT(count(result.begin(), result.end(), 1), 1);
}

TEST(RomanToInt, RomanToInt)
{
    string input = "LVIII";

    auto result = romanToInt(input);

    EXPECT_THAT(result, 58);
}