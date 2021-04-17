#pragma once

#include "steady_clock.h"

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace chapter_1 {

void findSmallestAndLargest(const std::vector<int>& array, int& smallest, int& largest);

struct Pair {
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
    CreditCard(std::shared_ptr<SteadyClock> clock, const std::string& no, 
        const std::string& nm, int lim, double bal=0);

    std::string getNumber() const { return m_number; }
    std::string getName() const { return m_name; }
    double getBalance() const { return m_balance; }
    int getLimit() const { return m_limit; }

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
    bool m_lateFeeCharged = false;
    std::chrono::steady_clock::time_point m_paymentDue{};
    std::shared_ptr<SteadyClock> m_clock;
};

std::ostream& operator<<(std::ostream& out, const CreditCard& c);

}