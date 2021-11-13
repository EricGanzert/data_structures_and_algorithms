#include "calendar.h"

#include <map>
#include <math.h>

using namespace std;

namespace calendar {

const map<Day, string> dayStrings = {{Day::Sunday, "Sunday"}, {Day::Monday, "Monday"}, 
    {Day::Tuesday, "Tuesday"}, {Day::Wednesday, "Wednesday"}, {Day::Thursday, "Thursday"}, 
    {Day::Friday, "Friday"}, {Day::Saturday, "Saturday"}};

const map<Month, string> monthStrings = {{Month::January, "January"}, {Month::February, "February"},
    {Month::March, "March"}, {Month::April, "April"}, {Month::May, "May"}, {Month::June, "June"}, 
    {Month::July, "July"}, {Month::August, "August"}, {Month::September, "September"},
    {Month::October, "October"}, {Month::November, "November"}, {Month::December, "December"}};

Day getDayEnum(uint32_t dayNumber)
{
    return static_cast<Day>(dayNumber);
}

string makeCenteredString(const string& background, const string& content)
{
    string result = background;
    auto index = (result.size() / 2) - (content.size() / 2);
    copy(content.begin(), content.end(), result.begin() + index);
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

CalendarMonth::CalendarMonth(Month month, uint32_t year)
    : m_month(month)
    , m_year(year)
{
    // main title
    m_chart += string(CellWidth * 7u, ' ') + "\n";
    m_chart += makeCenteredTitleString(month, year) + "\n";
    m_chart += string(CellWidth * 7u, ' ') + "\n";

    // make header with days of week
    for (const auto& day : dayStrings)
    {
        m_chart += makeCenteredDayString(day.first);
    }
    m_chart += '\n';

    auto startDay = getDayOfWeek(1u, m_month, m_year);
    auto totalDays = getNumDaysInMonth(m_month, m_year);

    auto daysMarked = 0u;

    for (auto weekIdx = 0u; weekIdx < 5u; ++weekIdx)
    {
        for (auto dayIdx = 0u; dayIdx < 7u; ++dayIdx)
        {
            if ((weekIdx == 0 && dayIdx < static_cast<uint32_t>(startDay))
                || (weekIdx == 4u && daysMarked >= totalDays))
            {
                makeCell(m_grid[weekIdx][dayIdx], "  ");
                continue;
            }
            makeCell(m_grid[weekIdx][dayIdx], to_string(daysMarked + 1));
            daysMarked++;
        }
    }

    fillChart();
}

void CalendarMonth::draw(ostream& stream)
{
    stream << m_chart;
}

void CalendarMonth::fillChart()
{
    for (auto week = 0u; week < NumWeeksPerMonth; ++week)
    {
        for (auto lineIdx = 0u; lineIdx < CellHeight; ++lineIdx)
        {
            for (auto day = 0u; day < NumDaysInWeek; ++day)
            {
                m_chart += m_grid[week][day][lineIdx];
            }
            m_chart += '\n';
        }
    }
}

} // namespace calendar