#pragma once

#include "calendar_utils.h"

#include <array>
#include <string>

namespace calendar {

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