#pragma once

#include <array>
#include <string>

namespace calendar {

constexpr uint32_t NumDaysInWeek = 7u;
constexpr uint32_t NumWeeksPerMonth = 5u;

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

std::array<Day, NumDaysInWeek> getWeek();

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
Month getMonthEnum(std::string month);

Day getDayOfWeek(uint32_t day, Month month, uint32_t year);

const uint32_t CellWidth = 13u;
const uint32_t CellHeight = 7u;

using Cell = std::array<std::string, CellHeight>;
void makeCell(Cell& cell, std::string value);

std::string makeCenteredDayString(Day day);
std::string makeCenteredTitleString(Month month, uint32_t year);

uint32_t getNumDaysInMonth(Month month, uint32_t year);
}