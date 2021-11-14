#include "calendar.h"

using namespace std;

namespace calendar {

CalendarMonth::CalendarMonth(Month month, uint32_t year)
    : m_month(month)
    , m_year(year)
{
    // main title
    m_chart += string(CellWidth * 7u, ' ') + "\n";
    m_chart += makeCenteredTitleString(month, year) + "\n";
    m_chart += string(CellWidth * 7u, ' ') + "\n";

    // make header with days of week
    const auto weekDays = getWeek();
    for (const auto& day : weekDays)
    {
        m_chart += makeCenteredDayString(day);
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