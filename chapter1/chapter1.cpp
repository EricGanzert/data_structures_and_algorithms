#include "chapter1.h"
#include "steady_clock.h"

#include <deque>
#include <functional>
#include <iostream>
#include <math.h>
#include <map>
#include <unordered_set>
#include <string>
#include <sstream>

using namespace std;
using namespace std::chrono;

void findSmallestAndLargest(const vector<int>& array, int& smallest, int& largest)
{
    if (array.empty())
    {
        return;
    }

    smallest = array.front();
    largest = array.front();

    for (auto item : array)
    {
        if (item < smallest)
        {
            smallest = item;
        }
        if (item > largest)
        {
            largest = item;
        }
    }
}

uint64_t sumOfIntsSmaller(uint32_t n)
{
    return ((uint64_t{n}-1)*uint64_t{n})/2;
}

bool isMultiple(long n, long m)
{
    // returns true if n == mi for some integer i
    if (n == 0)
    {
        return true;
    }

    if (m == 0)
    {
        return n==m;
    }

    auto i = n / m;
    if (i == 0)
    {
        return false;
    }
    return n == m * i;
}

void printArray(int** A, int m, int n)
{
    if (m < 1 || n < 1)
    {
        return;
    }
    
    for (int rowIndex = 0; rowIndex < m; ++rowIndex)
    {
        auto row = *(A + rowIndex);
        for (int index = 0; index < n; ++index)
        {
            cout << row[index] << " ";
        }
        cout << endl;
    }
}

    Flower::Flower(string name, int numPedals, float price) : m_name(name), m_numPedals(numPedals), m_price(price) {}

    string Flower::getName()
    {
        return m_name;
    }

    void Flower::setName(string name)
    {
        m_name = name;
    }

    int Flower::getNumPedals()
    {
        return m_numPedals;
    }

    void Flower::setNumPedals(int numPedals)
    {
        m_numPedals = numPedals;
    }

    float Flower::getPrice()
    {
        return m_price;
    }

    void Flower::setPrice(float price)
    {
        m_price = price;
    }

    CreditCard::CreditCard(shared_ptr<SteadyClock> clock, string no, 
        string nm, int lim, double bal)
        : m_number(no), m_name(nm), m_limit(lim), m_balance(bal), m_clock(clock)
    {
        m_payPeriodStart = m_clock->now();
    }

    bool CreditCard::chargeIt(double price)
    {
        if (price < 0 || price + m_balance > m_limit)
        {
            return false;
        }

        m_balance += price;
        return true;
    }

    void CreditCard::makePayment(double payment)
    {
        if (payment < 0)
        {
            return;
        }

        m_balance += payment * m_interestRate;
        m_balance -= payment;
        chargeFeeIfLate();
        m_payPeriodStart = m_clock->now();
    }

ostream& operator<<(ostream& out, const CreditCard& c)
{
    out << "Number = " << c.getNumber() << endl
        << "Name = " << c.getName() << endl
        << "Balance = " << c.getBalance() << endl
        << "Limit = " << c.getLimit() << endl;

    return out;
}

void CreditCard::chargeFeeIfLate()
{
    auto now = m_clock->now();
    auto timeDiff = now - m_payPeriodStart;

    if (timeDiff > 720h)
    {
        m_balance += m_lateFee;
    }
}

void CreditCard::setBalance(double balance)
{
    if (balance < 0.0)
    {
        return;
    }

    m_balance = balance;
}

void CreditCard::setLimit(double limit)
{
    if (limit < 0.0)
    {
        return;
    }

    m_limit = limit;
}

AllKinds::AllKinds(int integer, long longInt, float flt) 
    : m_int(integer), m_long(longInt), m_float(flt) {}

int AllKinds::getInt()
{
    return m_int;
}

void AllKinds::setInt(int newInt)
{
    m_int = newInt;
}

long AllKinds::getLongInt()
{
    return m_long;
}

void AllKinds::setLongInt(long newLong)
{
    m_long = newLong;
}

float AllKinds::getFloat()
{
    return m_float;
}

void AllKinds::setFloat(float newFloat)
{
    m_float = newFloat;
}

double AllKinds::sumOfAllCombos()
{
    return double(m_int * m_float + m_int * m_long + m_float * m_long);
}

bool twoPower(int i)
{
    if (i < 1)
    {
        return false;
    }

    // if you look at the bits representing the number,
    // it is a power of 2 if only one of the bits is set to 1
    auto sizeInBits = sizeof(i) * 8;
    auto andCount = 0u;
    auto bitCheck = 1ul;

    for (auto it = 0u; it < sizeInBits; it++, bitCheck <<= 1)
    {
        if (i & bitCheck)
        {
            andCount++;
        }
    }

    return andCount == 1;
}

uint64_t sumOfOddIntsSmaller(uint32_t n)
{
    auto numOdds = n / 2;
    return numOdds * numOdds;
}

uint32_t numDividesBy2Above2(double x)
{
    if (x < 2)
    {
        return 0u;
    }
    
    auto asInt = int64_t(x + 0.5);

    auto bits = log2(asInt);
    return bits - 1;
}

vector<int> reverseArray(const vector<int>& inputArray)
{
    vector<int> result;
    for (auto it = inputArray.rbegin(); it != inputArray.rend(); it++)
    {
        result.emplace_back(*it);
    }

    return result;
}

bool containsEvenProductOfPair(const std::vector<int>& inputArray)
{
    for (auto i = inputArray.begin(); i != inputArray.end(); ++i)
    {
        for (auto j = inputArray.begin(); j != inputArray.end(); ++j)
        {
            if (i != j && !((*i) * (*j) % 2))
            {
                return true;
            }
        }
    }
    return false;
}

bool allVectorElementsUnique(const vector<int>& inputArray)
{
    unordered_set<int> seen;
    for (const auto& item : inputArray)
    {
        if (seen.count(item))
        {
            return false;
        }
        seen.emplace(item);
    }
    return true;
}

void printOdds(ostream& outs, const vector<int>& inputArray)
{
    for (const auto& item : inputArray)
    {
        if (item % 2)
        {
            outs << item << " ";
        }
    }
    outs << endl;
}

void shuffleArray(vector<int>& inputArray)
{
    vector<int> shuffled(inputArray.size());
    deque<int> drawFrom(inputArray.begin(), inputArray.end());

    auto numRemaining = inputArray.size();

    for (auto& item : shuffled)
    {
        auto index = rand() % numRemaining;
        item = drawFrom[index];
        drawFrom.erase(drawFrom.begin() + index);
        numRemaining--;
    }

    swap(inputArray, shuffled);
}

namespace
{
void addLetter(ostream& outs, string output, char letter, const string& allLetters)
{
    if (output.find(letter) == string::npos)
    {
        output += letter;

        if (output.size() == allLetters.size())
        {
            if (!output.empty())
            {
                outs << " ";
            }
            outs << output;
            return;
        }

        for (char c : allLetters)
        {
            addLetter(outs, output, c, allLetters);
        }
    }
}
}

void allPossibleStrings(ostream& outs, const string& letters)
{
    for (char c : letters)
    {
        addLetter(outs, string(""), c, letters);
    }
}

void reverseLines(istream& ins, ostream& outs)
{
    string line;
    deque<string> allLines;
    
    while(getline(ins, line))
    {
        if (line.empty())
        {
            break;
        }
        allLines.emplace_back(line);
    }

    while(!allLines.empty())
    {
        outs << allLines.back() << endl;
        allLines.pop_back();
    }
}

vector<int> elementWiseProduct(const vector<int>& a, const vector<int>& b)
{
    if (a.size() != b.size())
    {
        throw runtime_error("element wise product for vectors of different sizes is undefined");
    }

    vector<int> result(a.size());
    for (auto idx = 0u; idx < result.size(); ++idx)
    {
        result[idx] = a[idx] * b[idx];
    }
    return result;
}

Vector2::Vector2() : m_data(Coordinate(0, 0))
{
}

Vector2::Vector2(double x, double y) : m_data(Coordinate(x, y))
{
}

Vector2::Vector2(Coordinate coordinate) : m_data(coordinate)
{
}

double Vector2::x() const
{
    return m_data.x;
}

double Vector2::y() const
{
    return m_data.y;
}

void Vector2::set(double x, double y)
{
    set(Coordinate(x, y));
}

void Vector2::set(Coordinate coordinate)
{
    m_data = coordinate;
}

Vector2::Coordinate Vector2::get() const
{
    return m_data;
}

Vector2::Coordinate::Coordinate(double x, double y) : x(x), y(y)
{}

Vector2::Coordinate::Coordinate() : x(0), y(0)
{}

const Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    Vector2::Coordinate coordinate(lhs.get());
    coordinate.x += rhs.x();
    coordinate.y += rhs.y();

    return Vector2(coordinate);
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    auto a = lhs.get();
    auto b = rhs.get();

    return a.x == b.x && a.y == b.y;
}

const Vector2 operator*(double coefficient, const Vector2& rhs)
{
    Vector2::Coordinate coordinate(rhs.get());
    coordinate.x *= coefficient;
    coordinate.y *= coefficient;

    return Vector2(coordinate);
}

const Vector2 operator*(const Vector2& lhs, double coefficient)
{
    return coefficient * lhs;
}

double dotProduct(const Vector2& vecA, const Vector2& vecB)
{
    auto a = vecA.get();
    auto b = vecB.get();

    return (a.x * b.x) + (a.y * b.y);
}

long powerOf2(uint32_t i)
{
    return 1 << i;
}

int gcd(int a, int b)
{
    if (!(a && b))
    {
        return 0;
    }

    if (abs(b) > abs(a))
    {
        auto temp = a;
        a = b;
        b = temp;
    }

    while(auto modulo = a % b)
    {
        a = b;
        b = modulo;
    }

    return abs(b);
}

void writeOutSentence(const std::string& sentence)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    auto randomAlphabetCharacter = [&] ()
    {
        return alphabet[rand() % alphabet.size()];
    };

    // pick 8 random numbers in between 1 and 100
    unordered_set<uint32_t> randomIndexes;
    while (randomIndexes.size() < 8ul)
    {
        auto index = rand() % 100;
        if (!randomIndexes.count(index))
        {
            randomIndexes.insert(index);
        }
    }

    for (auto i=0u; i<100u; ++i)
    {
        string line = sentence;
        if (randomIndexes.count(i))
        {
            line[rand() % line.size()] = randomAlphabetCharacter();
        }
        
        cout << to_string(i + 1) << ". " << line << endl;
    }
}

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