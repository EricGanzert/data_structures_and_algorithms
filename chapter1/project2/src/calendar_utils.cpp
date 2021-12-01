#include "calendar_utils.h"
#include <algorithm>
#include <map>
#include <math.h>
#include <stdexcept>

using namespace std;

namespace {
using namespace calendar;

const map<Day, string> dayStrings = {{Day::Sunday, "Sunday"}, {Day::Monday, "Monday"}, 
    {Day::Tuesday, "Tuesday"}, {Day::Wednesday, "Wednesday"}, {Day::Thursday, "Thursday"}, 
    {Day::Friday, "Friday"}, {Day::Saturday, "Saturday"}};

const map<Month, string> monthStrings = {{Month::January, "January"}, {Month::February, "February"},
    {Month::March, "March"}, {Month::April, "April"}, {Month::May, "May"}, {Month::June, "June"}, 
    {Month::July, "July"}, {Month::August, "August"}, {Month::September, "September"},
    {Month::October, "October"}, {Month::November, "November"}, {Month::December, "December"}};

string makeCenteredString(const string& background, const string& content)
{
    string result = background;
    auto index = (result.size() / 2) - (content.size() / 2);
    copy(content.begin(), content.end(), result.begin() + index);
    return result;
}

Day getDayEnum(uint32_t dayNumber)
{
    return static_cast<Day>(dayNumber);
}
} // namespace

namespace calendar {

Month getMonthEnum(std::string month)
{
    for (auto& c : month)
    {
        c = tolower(c);
    }

    for (auto m : monthStrings)
    {
        for (auto& c : m.second)
        {
            c = tolower(c);
        }

        if (month == m.second)
        {
            return m.first;
        }
    }
    throw runtime_error("did not recognize month string");
}

array<Day, NumDaysInWeek> getWeek()
{
    array<Day, NumDaysInWeek> result;
    auto iter = result.begin();

    for (const auto& day : dayStrings)
    {
        *iter = day.first;
        iter++;
    }
    return result;
}

string makeCenteredDayString(Day day)
{
    string line(CellWidth, ' ');
    return makeCenteredString(line, getDayString(day));
}

string makeCenteredTitleString(Month month, uint32_t year)
{
    string line(CellWidth * 7u, ' ');
    string title = getMonthString(month) + "  " + to_string(year);
    return makeCenteredString(line, title);
}

void makeCell(Cell& cell, string value)
{
    cell[0u] = string(CellWidth, '-');

    for (auto i = 0u; i < CellHeight; ++i)
    {
        if (i == 0 || i == CellHeight - 1)
        {
            continue;
        }
        string line(CellWidth, ' ');
        line.front() = '|';
        line.back() = '|';

        if (i == CellHeight / 2)
        {
            auto index = (CellWidth / 2) - (value.size() / 2);
            copy(value.begin(), value.end(), line.begin() + index);
        }
        cell[i] = line;
    }

    cell[cell.size() - 1] = string(CellWidth, '-');
}

string getDayString(Day day)
{
    return dayStrings.at(day);
}

string getMonthString(Month month)
{
    return monthStrings.at(month);
}

Day getDayOfWeek(uint32_t day, Month month, uint32_t year)
{
    if (day > 31)
    {
        string msg = "invalid day number: " + to_string(day);
        throw runtime_error(msg);
    }

    if (year > 9999)
    {
        string msg = "invalid year number: " + to_string(year);
        throw runtime_error(msg);
    }

    auto monthNumber = static_cast<uint32_t>(month);
    // convert the month number for our formula
    if (monthNumber < 3)
    {
        monthNumber += 12;
    }
    monthNumber -= 2;

    if (month == Month::January || month == Month::February)
    {
        year -= 1;
    }
    auto c = year / 100;
    auto y = year % 100;

    auto dayNumber = static_cast<int>(day + floor((2.6 * monthNumber) - 0.2) + y 
        + (y / 4) + (c / 4) - (2 * c)) % 7;

    if (dayNumber < 0)
    {
        dayNumber += 7;
    }

    return getDayEnum(dayNumber);    
}

uint32_t getNumDaysInMonth(Month month, uint32_t year)
{
    if (month == Month::April
        || month == Month::June
        || month == Month::September
        || month == Month::November)
    {
        return 30u;
    }
    if (month == Month::February)
    {
        if (year % 4 == 0)
        {
            return 29u;
        }
        return 28u;
    }
    return 31u;
}

} // namespace calendar