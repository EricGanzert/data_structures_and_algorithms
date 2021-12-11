#include "chapter2.h"

#include <algorithm>

using namespace std;

Progression::Progression(ostream& stream, long f) : outs(stream), first(f), cur(f) {}

void Progression::printProgression(int n)
{
    outs << firstValue();
    for (int i = 2; i <= n; i++)
    {
        outs << " " << nextValue();
    }
    outs << endl;
}

long Progression::firstValue()
{
    cur = first;
    return cur;
}

long Progression::nextValue()
{
    return ++cur;
}

FibonacciProgression::FibonacciProgression(ostream& stream, long f, long s) : Progression(stream, f), second(s) {}

long FibonacciProgression::firstValue()
{
    cur = first;
    prev = second - first;
    return cur;
}

long FibonacciProgression::nextValue()
{
    auto next = cur + prev;
    prev = cur;
    cur = next;
    return cur;
}

ArithProgression::ArithProgression(ostream& s, long i) : Progression(s), inc(i) {}

long ArithProgression::nextValue()
{
    cur += inc;
    return cur;
}

size_t countVowels(const string& line)
{
    const string vowels = "aeiou";
    size_t count{};

    for_each(line.begin(), line.end(), [&vowels, &count] (auto letter){
        if (vowels.find(tolower(letter)) != string::npos)
        {
            count++;
        }
    });

    if (!count)
    {
        if (line.find(string("y")) != string::npos)
        {
            count++;
        }
    }

    return count;
}