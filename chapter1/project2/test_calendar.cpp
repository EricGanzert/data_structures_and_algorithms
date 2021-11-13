#include "calendar.h"

#include <gmock/gmock.h>

using namespace calendar;
using namespace std;
using namespace testing;

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Calendar, MonthDraw)
{
    CalendarMonth november2021(Month::November, 2021);
    november2021.draw(cout);

    CalendarMonth march1994(Month::March, 1994);
    march1994.draw(cout);
}