#pragma once

#include "steady_clock.h"

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

void findSmallestAndLargest(const std::vector<int>& array, int& smallest, int& largest);

struct MyPair {
    int first{};
    double second{};
};

uint64_t sumOfIntsSmaller(uint32_t n);

// returns true if n == mi for some i
bool isMultiple(uint64_t n, uint64_t m);

void printArray(int** A, int m, int n);

class Flower {
public:
    Flower(std::string name, int numPedals, float price);

    std::string getName();
    void setName(std::string name);

    int getNumPedals();
    void setNumPedals(int numPedals);

    float getPrice();
    void setPrice(float price);

private:
    std::string m_name{};
    int m_numPedals{};
    float m_price{};
};

class CreditCard {
public:
    CreditCard(std::shared_ptr<SteadyClock> clock, std::string no, 
        std::string nm, int lim, double bal=0);

    std::string getNumber() const { return m_number; }
    void setNumber(std::string number) { m_number = number; }

    std::string getName() const { return m_name; }
    void setName(std::string name) { m_name = name; }

    double getBalance() const { return m_balance; }
    void setBalance(double balance);

    int getLimit() const { return m_limit; }
    void setLimit(double limit);

    bool chargeIt(double price);
    void makePayment(double payment);

private:
    void chargeFeeIfLate();

    std::string m_number;
    std::string m_name;
    int m_limit;
    double m_balance;

    const double m_interestRate = 0.02;
    const double m_lateFee = 10.00;
    std::chrono::steady_clock::time_point m_payPeriodStart{};
    std::shared_ptr<SteadyClock> m_clock;
};

std::ostream& operator<<(std::ostream& out, const CreditCard& c);


class AllKinds {
public:
    AllKinds() {}
    AllKinds(int integer, long longInt, float flt);
    
    int getInt();
    void setInt(int newInt);

    long getLongInt();
    void setLongInt(long newLong);

    float getFloat();
    void setFloat(float newFloat);

    double sumOfAllCombos();
private:
    int m_int{};
    long m_long{};
    float m_float{};
};