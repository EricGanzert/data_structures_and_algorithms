#include <calendar.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace calendar;
using namespace std;

namespace {
const unordered_set<string> months = {"january", "february", "march", "april", 
    "may", "june", "july", "august", "september", "october", "november", "december"};
}

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        cout << "usage is calendar_month <month> <year>" << endl;
        exit(1);
    }

    const string month(argv[1]);
    const string year(argv[2]);

    bool monthGood = true;
    bool yearGood = true;

    auto lowercaseMonth = month;
    for (auto& c : lowercaseMonth)
    {
        c = tolower(c);
    }
    
    if(!months.count(lowercaseMonth))
    {
        cout << "error, did not recognize month: " << month << endl;
        monthGood = false;
    }

    auto yearInt = stoi(year);
    if (!(yearInt > 0 && yearInt < 10000))
    {
        cout << "error, did not recognize year: " << year << endl
            << "must be a number > 0 and maximum 9999" << endl;
        yearGood = false;
    }

    if (!(monthGood && yearGood))
    {
        exit(1);
    }

    CalendarMonth requestedMonth(getMonthEnum(month), yearInt);
    requestedMonth.draw(cout);
}