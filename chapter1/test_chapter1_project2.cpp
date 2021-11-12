#include "chapter1.h"

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// P-1.2
TEST(Calendar, DayOfWeekFunction)
{
    EXPECT_THAT(getDayString(getDayOfWeek(12, Month::November, 2021)), "Friday");
    EXPECT_THAT(getDayString(getDayOfWeek(6, Month::January, 2003)), "Monday");
    EXPECT_THAT(getDayString(getDayOfWeek(12, Month::May, 1933)), "Friday");
}