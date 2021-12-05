
class Progression {
public:
    // f is the starting value of the progression
    Progression(long f = 0);
    virtual ~Progression() = default;
    // print the first n values
    void printProgression(int n);

protected:
    virtual long firstValue();
    virtual long nextValue();

    long first{};
    long cur{};
};