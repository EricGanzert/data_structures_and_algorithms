#include <atomic>
#include <condition_variable>
#include <iostream>
#include <deque>
#include <list>
#include <map>
#include <math.h>
#include <mutex>
#include <thread>
#include <unordered_set>

template<typename T>
class Progression {
public:
    // f is the starting value of the progression
    Progression(std::ostream& stream, T f = 0) : outs(stream), first(f), cur(f) {}
    virtual ~Progression() = default;
    // print the first n values
    void printProgression(int n)
    {
        outs << firstValue();
        for (int i = 2; i <= n; i++)
        {
            outs << " " << nextValue();
        }
        outs << std::endl;
    }

protected:
    virtual T firstValue()
    {
        cur = first;
        return cur;
    }
    virtual T nextValue()
    {
        return ++cur;
    }

    std::ostream& outs;
    T first{};
    T cur{};
};

class FibonacciProgression : public Progression<long> {
public:
    FibonacciProgression(std::ostream& stream, long f = 0, long s = 1);
protected:
    virtual long firstValue();
    virtual long nextValue();

    long second{};
    long prev{};
};

class ArithProgression : public Progression<long> {
public:
    ArithProgression(std::ostream& s, long i = 1);
protected:
    virtual long nextValue();
    long inc{};
};

class AbsDifference : public Progression<long> {
public:
    AbsDifference(std::ostream& outs);
    AbsDifference(std::ostream& outs, long f, long s);

    void printProgression(int n);
protected:
    virtual long nextValue();
    virtual long firstValue();
    virtual long secondValue();

    long second{};
    long prev{};
};

class SqrtProgression : public Progression<double> {
public:
    SqrtProgression(std::ostream& outs) : Progression(outs, 65'536.0) {}
    SqrtProgression(std::ostream& outs, double f) : Progression(outs, f) {}
protected:
    virtual double nextValue();
};

class Object
{ public: virtual void printMe() = 0; };
class Place : public Object
{ public: virtual void printMe() {std::cout << "Buy it." << std::endl;} };
class Region : public Place
{ public: virtual void printMe() {std::cout << "Box it." << std::endl;} };
class State : public Region
{ public: virtual void printMe() {std::cout << "Ship it." << std::endl;} };
class MaryLand : public State
{ public: virtual void printMe() {std::cout << "Read it." << std::endl;} };

size_t countVowels(const std::string& line);

void removePunctuation(std::string& s);

bool correctArithmeticFormula(int a, int b, int c);

template<typename A, typename B>
class MyPair {
public:
    MyPair(A first, B second) : m_first(first)
        , m_second(second) {}

    A first() {return m_first;}
    B second() {return m_second;}

private:        
    A m_first{};
    B m_second{};
};

enum class MyType : int {
    One,
    Two,
    Three
};

void hasUnreachableCode(MyType arg);

// represents a line y = a*x + b
class Line {
public:
    Line(double a, double b);
    double intersect(const Line& line);
    double a() const;
    double b() const;

private:
    double m_a{};
    double m_b{};
};

class A {
public:
    virtual int getX() { return x; }
protected:
    int x = 1;
};

class B : public A {
public:
    virtual int getX() { return x; }
protected:
    int x = 2;
};

class C final : public B {
public:
    virtual int getX() { return x; }
    int getXFromBase() { return A::x; };
private:
    int x = 3;
};

using Packet = uint32_t;

class InternetUser;

class Internet {
public:
    Internet();
    ~Internet();

    bool sendPacket(Packet packet, std::shared_ptr<InternetUser> recipient);

private:
    void deliveryWorker();

    std::deque<std::pair<Packet, std::shared_ptr<InternetUser>>> m_toSend;
    std::mutex m_packetMutex;

    std::atomic<bool> m_keepDelivering;
    std::thread m_deliveryThread;
};

class InternetUser {
public:
    InternetUser(std::string name, std::shared_ptr<Internet> internet);
    virtual ~InternetUser();

    void sendPacket(Packet packet, std::shared_ptr<InternetUser> recipient);
    void receivePacket(Packet packet);

    size_t numPacketsProcessed();
    Packet lastPacketProcessed();
private:
    std::string m_name;
    std::shared_ptr<Internet> m_internet;

    std::deque<Packet> m_arrivedPackets;
    std::mutex m_arrivedPacketsMutex;

    void processPackets();
    std::atomic<bool> m_processPackets;
    std::thread m_pktProcessThread;
    std::atomic<size_t> m_numPacketsProcessed{};
    std::atomic<Packet> m_lastPacketProcessed{};
};

class Term {
public:
    Term(double coefficient, int exponent);
    void print(std::ostream& outs = std::cout) const;
    void derive();

    double coefficient() const;
    int exponent() const;

private:
    double m_coefficient{};
    int m_exponent{};
};

class Polynomial {
public:
    Polynomial(const std::vector<Term>& terms, std::ostream& outs = std::cout);
    void derive();
    void print() const;
private:
    std::vector<Term> m_termList;
    std::ostream& m_outs;
};

// returns the number of times you can divide arg by 2 before it becomes less than 2
// arg must be greater than 2 or else the function will return 0
size_t numTimesDivideBy2(int arg);

namespace money {
using Count = size_t;
using ValueCents = uint32_t;
using Change = std::map<ValueCents, Count, std::greater<>>;
Change makeChange(double charged, double given);
}

template <typename T>
class Vector {
public:
    Vector(size_t size) : m_vec(size, T{})
    {}

    size_t size() const
    {
        return m_vec.size();
    }

    T& at(size_t index)
    {
        if (index >= size())
        {
            throw runtime_error("Error: Trying to access element out of range");
        }

        return m_vec[index];
    }

    const T& at(size_t index) const
    {
        if (index >= size())
        {
            throw runtime_error("Error: Trying to access element out of range");
        }

        return m_vec[index];
    }
private:
    std::vector<T> m_vec;
};

template <typename T>
Vector<T> operator +(const Vector<T>& a, const Vector<T>& b)
{
    if (a.size() != b.size())
    {
        throw runtime_error("Error: Trying to add vectors of different sizes");
    }
    
    Vector<T> result(a.size());
    for (auto i=0u; i<result.size(); i++)
    {
        result.at(i) = a.at(i) + b.at(i);
    }
    return result;
}

template <typename T>
Vector<T> operator -(const Vector<T>& a, const Vector<T>& b)
{
    if (a.size() != b.size())
    {
        throw runtime_error("Error: Trying to subtract vectors of different sizes");
    }
    
    Vector<T> result(a.size());
    for (auto i=0u; i<result.size(); i++)
    {
        result.at(i) = a.at(i) - b.at(i);
    }
    return result;
}


template <typename T>
Vector<T> operator *(const T& scalar, const Vector<T>& vec)
{
    Vector<T> result(vec.size());
    for (auto i=0u; i < vec.size(); i++)
    {
        result.at(i) = vec.at(i) * scalar;
    }
    return result;
}

template <typename T>
Vector<T> operator *(const Vector<T>& vec, const T& scalar)
{
    return scalar * vec;
}

template <typename T>
T operator *(const Vector<T>& a, const Vector<T>& b)
{
    if (a.size() != b.size())
    {
        throw runtime_error("Error: Trying to find dot product for vectors of different sizes");
    }
    T result{};

    for (auto i=0u; i<a.size(); i++)
    {
        result += a.at(i) * b.at(i);
    }
    return result;
}

class Complex {
public:
    Complex();
    Complex(double i, double j = 0.0);
    double i() const;
    double j() const;

private:
    double m_i{};
    double m_j{};
};

Complex operator +(const Complex& lhs, const Complex& rhs);
Complex& operator +=(Complex& lhs, const Complex& rhs);

Complex operator -(const Complex& lhs, const Complex& rhs);
Complex operator *(const Complex& lhs, const Complex& rhs);

bool operator ==(const Complex& lhs, const Complex& rhs);

class Animal {
public:
    Animal(bool gender, float strength)
        : m_gender(gender), m_strength(strength) {}
    
    virtual ~Animal() = default;

    bool gender() {return m_gender;}
    float strength() {return m_strength;}

    virtual std::string speciesName() = 0;

private:
    bool m_gender{};
    float m_strength{};
};

class Chicken : public Animal {
public:
    Chicken(bool gender, float strength)
        : Animal(gender, strength) {}

    virtual std::string speciesName() override
    {
        return std::string("Chicken");
    }
};

class Dog : public Animal {
public:
    Dog(bool gender, float strength)
        : Animal(gender, strength) {}

    virtual std::string speciesName() override
    {
        return std::string("Dog");
    }
};

std::shared_ptr<Animal> interact(std::shared_ptr<Animal>& a, std::shared_ptr<Animal>& b);
