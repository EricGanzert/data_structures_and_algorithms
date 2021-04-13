#include "chapter1.h"

#include <iostream>

using namespace std;

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

bool isMultiple(uint64_t n, uint64_t m)
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

    if (n < m && n != 0)
    {
        return false;
    }

    auto i = n / m;
    return m == n / i;
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


    CreditCard::CreditCard(const string& no, 
        const string& nm, int lim, double bal)
        : m_number(no), m_name(nm), m_limit(lim), m_balance(bal)
    {}

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
        m_balance -= payment;
    }

ostream& operator<<(ostream& out, const CreditCard& c)
{
    out << "Number = " << c.getNumber() << endl
        << "Name = " << c.getName() << endl
        << "Balance = " << c.getBalance() << endl
        << "Limit = " << c.getLimit() << endl;

    return out;
}