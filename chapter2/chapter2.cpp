#include "chapter2.h"

#include <algorithm>
#include <functional>
#include <type_traits>

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

AbsDifference::AbsDifference(ostream& outs) : Progression(outs, 2), second(200) {}

AbsDifference::AbsDifference(ostream& outs, long f, long s) : Progression(outs, f), second(s) {}

long AbsDifference::nextValue()
{
    auto temp = cur;
    cur = abs(cur - prev);
    prev = temp;
    return cur;
}

long AbsDifference::firstValue()
{
    prev = first;
    return prev;
}

long AbsDifference::secondValue()
{
    cur = second;
    return cur;
}

void AbsDifference::printProgression(int n)
{
    outs << firstValue() << " " << secondValue();

    for (auto i = 2; i < n; ++i)
    {
        outs << " " << nextValue();
    }
    outs << endl;
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
        if (line.find("y") != string::npos)
        {
            count++;
        }
    }

    return count;
}

void removePunctuation(string& s)
{
    string result;
    const string allowed = " abcdefghijklmnopqrstuvwxyz";
    for (auto letter : s)
    {
        if (allowed.find(tolower(letter)) != string::npos)
        {
            result += letter;
        }
    }

    swap(s, result);
}

using IntOperator = function<int(int, int)>; 

bool division(IntOperator op)
{
    return op.target_type() == IntOperator(divides<int>()).target_type();
}

bool correctArithmeticFormula(int a, int b, int c)
{
    // a + b = c
    // a - b = c
    // a * b = c
    // a / b = c

    // a = b + c
    // a = b - c
    // a = b * c
    // a = b / c

    vector<IntOperator> operators = {plus<int>(), minus<int>(), multiplies<int>(), divides<int>()};
    for (auto& op : operators)
    {
        auto isDivide = division(op);
        if (!(isDivide && b == 0))
        {
            if (op(a, b) == c)
            {
                return true;
            }
        }

        if (!(isDivide && c == 0))
        {
            if (a == op(b, c))
            {
                return true;
            }
        }
    }

    return false;
}

// C-2.3
void hasUnreachableCode(MyType arg)
{
    switch(arg)
    {
    case MyType::One:
        cout << "One" << endl;
        break;
    case MyType::Two:
        cout << "Two" << endl;
        break;
    case MyType::Three:
        cout << "Three" << endl;
        break;
    default:
        // This code is unreachable unless MyType definition is changed.
        // Should still be compiled though 
        cout << "Unknown" << endl;
    };
}

Line::Line(double a, double b) : m_a(a), m_b(b)
{}

double Line::a() const
{
    return m_a;
}

double Line::b() const
{
    return m_b;
}

double Line::intersect(const Line& line)
{
    if (line.a() == m_a)
    {
        throw runtime_error("Lines are parallel");
    }

    return (line.b() - m_b) / (m_a - line.a());
}
