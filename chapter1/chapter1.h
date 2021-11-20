#pragma once

#include "steady_clock.h"

#include <chrono>
#include <cstdint>
#include <iostream>
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
bool isMultiple(long n, long m);

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

// returns true if i is a power of 2. Does not use multiplication or division
bool twoPower(int i);

uint64_t sumOfOddIntsSmaller(uint32_t n);

uint32_t numDividesBy2Above2(double x);

std::vector<int> reverseArray(const std::vector<int>& inputArray);

bool containsEvenProductOfPair(const std::vector<int>& inputArray);

bool allVectorElementsUnique(const std::vector<int>& inputArray);

void printOdds(std::ostream& outs, const std::vector<int>& inputArray);

void shuffleArray(std::vector<int>& inputArray);

void allPossibleStrings(std::ostream& outs, const std::string& letters);

void reverseLines(std::istream& ins, std::ostream& outs);

// will throw an exception if the vectors provided are not the same size
std::vector<int> elementWiseProduct(const std::vector<int>& a, const std::vector<int>& b);

class Vector2 {
public:
    struct Coordinate {
        Coordinate(double x, double y);
        Coordinate();
        double x{};
        double y{};
    };

    Vector2();
    Vector2(double x, double y);
    Vector2(Coordinate coordinate);

    double x() const;
    double y() const;
    void set(double x, double y);
    void set(Coordinate coordinate);
    Coordinate get() const;
private:
    Coordinate m_data;
};

const Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

bool operator==(const Vector2& lhs, const Vector2& rhs);

const Vector2 operator*(double coefficient, const Vector2& rhs);

const Vector2 operator*(const Vector2& lhs, double coefficient);

double dotProduct(const Vector2& vecA, const Vector2& vecB);

long powerOf2(uint32_t i);

int gcd(int a, int b);

void writeOutSentence(const std::string& sentence);

std::vector<uint32_t> getRandomBirthdays(uint32_t n);

bool sharedBirthday(uint32_t n);