#include <iostream>

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
        outs << endl;
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
