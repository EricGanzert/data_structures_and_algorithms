#include <atomic>
#include <condition_variable>
#include <iostream>
#include <deque>
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
    Term(double coefficient, int exponent, std::ostream& outs = std::cout);
    void print();
    void derive();

private:
    std::ostream& m_outs;
    double m_coefficient{};
    int m_exponent{};
};
