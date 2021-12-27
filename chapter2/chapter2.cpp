#include "chapter2.h"

#include <algorithm>
#include <array>
#include <functional>
#include <type_traits>

using namespace std;

namespace {
bool doubleEq(double a, double b)
{
    return fabs(a - b) < 0.000001;
}
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

double SqrtProgression::nextValue()
{
    cur = sqrt(cur);
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

Internet::Internet() : m_keepDelivering(true)
    , m_deliveryThread(&Internet::deliveryWorker, this)
{}

Internet::~Internet()
{
    m_keepDelivering = false;
    m_deliveryThread.join();
}

bool Internet::sendPacket(Packet packet, shared_ptr<InternetUser> recipient)
{
    if (!recipient)
    {
        return false;
    }

    lock_guard<mutex> lk(m_packetMutex);
    m_toSend.emplace_back(make_pair(move(packet), recipient));
    return true;
}

void Internet::deliveryWorker()
{
    while (m_keepDelivering)
    {
        decltype(m_toSend)::value_type packetInfo{};
        {
            lock_guard<mutex> lk(m_packetMutex);
            if (m_toSend.empty())
            {
                continue;
            }
            packetInfo = m_toSend.front();
            m_toSend.pop_front();
        }
        packetInfo.second->receivePacket(packetInfo.first);
    }
}

InternetUser::InternetUser(string name, shared_ptr<Internet> internet)
    : m_name(name)
    , m_internet([&internet] {
        if (!internet)
        {
            throw runtime_error("InternetUser created with null internet");
        }
        return internet;
        }())
    , m_processPackets(true) 
    , m_pktProcessThread(&InternetUser::processPackets, this)
{
}

InternetUser::~InternetUser()
{
    m_processPackets = false;
    m_pktProcessThread.join();
}

void InternetUser::sendPacket(Packet packet, shared_ptr<InternetUser> recipient)
{
    // cout << "User " << m_name << " sends packet: " << packet << endl;
    m_internet->sendPacket(packet, recipient);
}

void InternetUser::receivePacket(Packet packet)
{
    lock_guard<mutex> lk(m_arrivedPacketsMutex);
    m_arrivedPackets.emplace_back(packet);
}

void InternetUser::processPackets()
{
    while(m_processPackets)
    {
        decltype(m_arrivedPackets)::value_type packet{};
        {
            lock_guard<mutex> lk(m_arrivedPacketsMutex);
            if (m_arrivedPackets.empty())
            {
                continue;
            }

            packet = m_arrivedPackets.front();
            m_arrivedPackets.pop_front();
        }
        // cout << "User " << m_name << " received packet: " << packet << endl;
        m_numPacketsProcessed++;
        m_lastPacketProcessed = packet;
    }
}

size_t InternetUser::numPacketsProcessed()
{
    return m_numPacketsProcessed;
}

Packet InternetUser::lastPacketProcessed()
{
    return m_lastPacketProcessed;
}


Term::Term(double coefficient, int exponent) : 
    m_coefficient(coefficient)
    , m_exponent(exponent)
{}

void Term::print(ostream& outs) const
{
    outs << (m_coefficient > 0 ? "+" : "-") << m_coefficient << "x^" << m_exponent;
}

void Term::derive()
{
    m_coefficient *= m_exponent;
    m_exponent--;
}

double Term::coefficient() const
{
    return m_coefficient;
}

int Term::exponent() const
{
    return m_exponent;
}

bool operator >(const Term& a, const Term& b)
{
    return a.exponent() > b.exponent();
}

Polynomial::Polynomial(const vector<Term>& terms, ostream& outs)
    : m_termList([&]{
        decltype(m_termList) t(terms);
        sort(t.begin(), t.end(), greater<>());
        return move(t);
    }())
    , m_outs(outs)
{}

void Polynomial::derive()
{
    for (auto item = m_termList.begin(); item != m_termList.end();)
    {
        item->derive();
        if (item->exponent() < 0)
        {
            item = m_termList.erase(item);
            continue;
        }
        item++;
    }
}

void Polynomial::print() const
{
    for (auto& item : m_termList)
    {
        item.print(m_outs);
    }
}

size_t numTimesDivideBy2(int arg)
{
    if (arg <= 2)
    {
        return 0;
    }

    return size_t(log2(arg));
}

namespace money {

Change makeChange(double charged, double given)
{
    Change result{};
    if (given <= charged)
    {
        return result;
    }

    auto diffCents = ValueCents(((given - charged) * 100) + 0.5);

    constexpr array<ValueCents, 11> CentDenominations = 
        {10000, 5000, 2000, 1000, 500, 200, 100, 25, 10, 5, 1};

    for (const auto& cents : CentDenominations)
    {
        while (diffCents / cents)
        {
            result[cents]++;
            diffCents -= cents;
        }
    }

    return result;
}
}

Complex::Complex()
    : m_i(0)
    , m_j(0)
{}

Complex::Complex(double i, double j)
    : m_i(i)
    , m_j(j)
{}

double Complex::i() const
{
    return m_i;
}

double Complex::j() const
{
    return m_j;
}

Complex operator +(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.i() + rhs.i(), lhs.j() + rhs.j());
}

Complex& operator +=(Complex& lhs, const Complex& rhs)
{
    lhs = Complex((lhs.i() + rhs.i()), (lhs.j() + rhs.j()));
    return lhs;
}

Complex operator -(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.i() - rhs.i(), lhs.j() - rhs.j());
}

Complex operator *(const Complex& lhs, const Complex& rhs)
{
    auto i1 = lhs.i();
    auto j1 = lhs.j();

    auto i2 = rhs.i();
    auto j2 = rhs.j();

    return Complex((i1*i2 - j1*j2), (i1*j2 + i2*j1));
}

bool operator ==(const Complex& lhs, const Complex& rhs)
{
    return doubleEq(lhs.i(), rhs.i()) && doubleEq(lhs.j(), rhs.j());
}
