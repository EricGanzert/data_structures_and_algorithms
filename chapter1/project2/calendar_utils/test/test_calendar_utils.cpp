#include "calendar_utils.h"

#include <gmock/gmock.h>

using namespace calendar;
using namespace std;
using namespace testing;

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Calendar, DayOfWeekFunction)
{
    EXPECT_THAT(getDayString(getDayOfWeek(12, Month::November, 2021)), "Friday");
    EXPECT_THAT(getDayString(getDayOfWeek(6, Month::January, 2003)), "Monday");
    EXPECT_THAT(getDayString(getDayOfWeek(12, Month::May, 1933)), "Friday");
}

TEST(Calendar, MakeCell)
{
    auto printCell = [](const Cell& cell)
    {
        for (const auto& line : cell)
        {
            cout << line << endl;
        }
    };

    Cell myCell{};
    makeCell(myCell, "21");
    printCell(myCell);
}