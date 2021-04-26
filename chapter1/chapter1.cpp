#include "chapter1.h"
#include "steady_clock.h"

#include <iostream>

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