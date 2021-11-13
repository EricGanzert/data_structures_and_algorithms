#pragma once

#include <array>
#include <string>

namespace calendar {

enum class Day : uint32_t {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

std::string getDayString(Day day);

enum class Month : uint32_t {
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

std::string getMonthString(Month month);

Day getDayOfWeek(uint32_t day, Month month, uint32_t year);

constexpr uint32_t NumDaysInWeek = 7u;
constexpr uint32_t NumWeeksPerMonth = 5u;

const uint32_t CellWidth = 13u;
const uint32_t CellHeight = 7u;

using Cell = std::array<std::string, CellHeight>;
void makeCell(Cell& cell, std::string value);

class CalendarMonth {
public:
    CalendarMonth() = delete;
    CalendarMonth(Month month, uint32_t year);

    void draw(std::ostream& stream);

private:
    void fillChart();

    Month m_month;
    uint32_t m_year{};
    std::string m_chart;
    std::array<std::array<Cell, 7u>, 5u> m_grid{};
};

} // namespace calendar