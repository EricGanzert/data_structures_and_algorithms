#include "chapter1.h"
#include "steady_clock.h"

#include <deque>
#include <functional>
#include <iostream>
#include <math.h>
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

Vector2::Coordinate::Coordinate(double x, double y) : x(x), y(y)
{}

size_t Vector2::size() const
{
    return m_data.size(); 
}

void Vector2::pushBack(Vector2::Coordinate coordinate)
{
    m_data.push_back(coordinate);
}

void Vector2::pushBack(double x, double y)
{
    m_data.push_back(Vector2::Coordinate(x, y));
}

const Vector2::Coordinate Vector2::at(size_t index) const
{
    return m_data[index];
}

const Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    if (lhs.size() != rhs.size())
    {
        throw runtime_error("cannot add 2 vectors of differing sizes");
    }

    Vector2 result;
    for (auto index = 0u; index < lhs.size(); ++index)
    {
        auto coordinate = lhs.at(index);
        coordinate.x += rhs.at(index).x;
        coordinate.y += rhs.at(index).y;
        result.pushBack(coordinate);
    }
    return result;
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }

    for (auto idx = 0u; idx < lhs.size(); ++idx)
    {
        auto a = lhs.at(idx);
        auto b = rhs.at(idx);

        if (!(a.x == b.x && a.y == b.y))
        {
            return false;
        }
    }

    return true;
}

const Vector2 operator*(double coefficient, const Vector2& rhs)
{
    Vector2 result;
    for (auto index = 0u; index < rhs.size(); ++index)
    {
        auto coordinate = rhs.at(index);
        coordinate.x *= coefficient;
        coordinate.y *= coefficient;
        result.pushBack(coordinate);
    }
    return result;
}

const Vector2 operator*(const Vector2& lhs, double coefficient)
{
    return coefficient * lhs;
}
