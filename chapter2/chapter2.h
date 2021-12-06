#include <iostream>

class Progression {
public:
    // f is the starting value of the progression
    Progression(std::ostream& stream, long f = 0);
    virtual ~Progression() = default;
    // print the first n values
    void printProgression(int n);

protected:
    virtual long firstValue();
    virtual long nextValue();

    std::ostream& outs;
    long first{};
    long cur{};
};

class FibonacciProgression : public Progression {
public:
    FibonacciProgression(std::ostream& stream, long f = 0, long s = 1);
protected:
    virtual long firstValue();
    virtual long nextValue();

    long second{};
    long prev{};
};