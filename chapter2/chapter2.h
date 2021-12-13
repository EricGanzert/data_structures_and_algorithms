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

class ArithProgression : public Progression {
public:
    ArithProgression(std::ostream& s, long i = 1);
protected:
    virtual long nextValue();
    long inc{};
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
