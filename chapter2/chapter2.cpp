#include "chapter2.h"

#include <iostream>

using namespace std;

Progression::Progression(long f) : first(f), cur(f) {}

void Progression::printProgression(int n)
{
    cout << firstValue();
    for (int i = 2; i <= n; i++)
    {
        cout << " " << nextValue();
    }
    cout << endl;
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