#include "chapter2.h"

#include <algorithm>
#include <array>
#include <functional>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>

using namespace std;

namespace {
bool doubleEq(double a, double b, double tolerance = 0.000001)
{
    return fabs(a - b) < tolerance;
}

constexpr auto Pi = 3.14159265;

struct DoubleEqComparator {
    bool operator()(const double& a, const double& b) const {
        return doubleEq(a, b);
    };
};

using UniqueDoublesContainer = unordered_set<double, hash<double>, DoubleEqComparator>;

pair<size_t, size_t> distinctPoints(const vector<Vertex>& vertices)
{
    UniqueDoublesContainer uniqueX;
    UniqueDoublesContainer uniqueY;

    for (const auto& element : vertices)
    {
        uniqueX.insert(element.first);
        uniqueY.insert(element.second);
    }

    return make_pair<size_t, size_t>(uniqueX.size(), uniqueY.size());
}

bool isTriangle(const vector<Vertex>& vertices)
{
    if (vertices.size() != 3)
    {
        return false;
    }

    auto points = distinctPoints(vertices);
    return points.first > 1 && points.second > 1;
}

array<double, 3> triangleSideLengths(const vector<Vertex>& vertices)
{
    if (!isTriangle(vertices))
    {
        throw runtime_error("Invalid input to triangleSideLengths");
    }

    auto x1 = vertices[0].first;
    auto y1 = vertices[0].second;

    auto x2 = vertices[1].first;
    auto y2 = vertices[1].second;

    auto x3 = vertices[2].first;
    auto y3 = vertices[2].second;

    auto lengthA = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    auto lengthB = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    auto lengthC = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));

    array<double, 3> result = {lengthA, lengthB, lengthC};
    return result;
}

bool isIsoscelesTriangle(const vector<Vertex>& vertices)
{
    if (!isTriangle(vertices))
    {
        return false;
    }

    auto sideLengths = triangleSideLengths(vertices);

    return (doubleEq(sideLengths[0], sideLengths[1]) && !doubleEq(sideLengths[0], sideLengths[2])) 
        || (doubleEq(sideLengths[1], sideLengths[2]) && !doubleEq(sideLengths[1], sideLengths[0])) 
        || (doubleEq(sideLengths[2], sideLengths[0])  && !doubleEq(sideLengths[2], sideLengths[1]));
}

bool isEquilateralTriangle(const vector<Vertex>& vertices)
{
    if (!isTriangle(vertices))
    {
        return false;
    }

    auto sideLengths = triangleSideLengths(vertices);

    return doubleEq(sideLengths[0], sideLengths[1]) && doubleEq(sideLengths[1], sideLengths[2]);
}

bool isQuadrilateral(const vector<Vertex>& vertices)
{
    if (vertices.size() != 4)
    {
        return false;
    }

    auto points = distinctPoints(vertices);
    return points.first > 1 && points.second > 1;
}

array<double, 4> quadrilateralSideLengths(const vector<Vertex>& vertices)
{
    if (!isQuadrilateral(vertices))
    {
        throw runtime_error("Invalid input to quadrilateralSideLengths");
    }

    auto x1 = vertices[0].first;
    auto y1 = vertices[0].second;

    auto x2 = vertices[1].first;
    auto y2 = vertices[1].second;

    auto x3 = vertices[2].first;
    auto y3 = vertices[2].second;

    auto x4 = vertices[3].first;
    auto y4 = vertices[3].second;
    
    auto lengthA = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    auto lengthB = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    auto lengthC = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
    auto lengthD = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2));

    array<double, 4> result = {lengthA, lengthB, lengthC, lengthD};
    return result;
}

bool isRectangle(const vector<Vertex>& vertices)
{
    if (!isQuadrilateral(vertices))
    {
        return false;
    }

    auto sideLengths = quadrilateralSideLengths(vertices);

    UniqueDoublesContainer uniqueLengths;
    for (const auto& length : sideLengths)
    {
        uniqueLengths.insert(length);
    }

    return uniqueLengths.size() > 0 && uniqueLengths.size() < 3;
}

bool isSquare(const vector<Vertex>& vertices)
{
    if (!isRectangle(vertices))
    {
        return false;
    }

    auto sideLengths = quadrilateralSideLengths(vertices);

    UniqueDoublesContainer uniqueLengths;
    for (const auto& length : sideLengths)
    {
        uniqueLengths.insert(length);
    }

    return uniqueLengths.size() == 1;
}

bool isPentagon(const vector<Vertex>& vertices)
{
    if (vertices.size() != 5)
    {
        return false;
    }

    auto points = distinctPoints(vertices);
    return points.first >= 3 && points.second >= 3 && (points.first + points.second) >= 8;
}

bool isHexagon(const vector<Vertex>& vertices)
{
    if (vertices.size() != 6)
    {
        return false;
    }

    auto points = distinctPoints(vertices);
    return points.first >= 3 && points.second >= 3 && (points.first + points.second) >= 7;
}

bool isOctagon(const vector<Vertex>& vertices)
{
    if (vertices.size() != 8)
    {
        return false;
    }

    auto points = distinctPoints(vertices);
    return points.first >= 4 && points.second >= 4 && (points.first + points.second) >= 8;
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
        {
            lock_guard<mutex> lk(m_packetStatsMutex);
            m_numPacketsProcessed++;
            m_lastPacketProcessed = packet;
        }
    }
}

size_t InternetUser::numPacketsProcessed()
{
    lock_guard<mutex> lk(m_packetStatsMutex);
    return m_numPacketsProcessed;
}

Packet InternetUser::lastPacketProcessed()
{
    lock_guard<mutex> lk(m_packetStatsMutex);
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
        return t;
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

shared_ptr<Animal> interact(shared_ptr<Animal>& a, shared_ptr<Animal>& b)
{
    // if they are different types of Animal nothing happens
    if (a->speciesName() != b->speciesName())
    {
        return nullptr;
    }

    // if they are different genders they will create a new animal
    if (a->gender() != b->gender())
    {
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> genders(0,1);
        auto gender = static_cast<bool>(genders(rng));
        auto strength = (a->strength() + b->strength()) / 2;

        if (a->speciesName() == string("Dog"))
        {
            return make_shared<Dog>(gender, strength);
        }
        else if (a->speciesName() == string("Chicken"))
        {
            return make_shared<Chicken>(gender, strength);
        }
        else
        {
            throw runtime_error("unknown Animal type");
        }
    }

    // when both are the same gender only the stronger one will survive
    if (a->strength() < b->strength())
    {
        a.reset();
    }
    else
    {
        b.reset();
    }
    return nullptr;
}


Triangle::Triangle(double height, double width)
    : m_height(height)
    , m_width(width)
{}

double Triangle::area() const
{
    return (m_height * m_width) / 2;
}

double Triangle::perimeter() const
{
    return m_height + m_width + sqrt(m_height * m_height + m_width * m_width);
}

IsoscelesTriangle::IsoscelesTriangle(double height, double width)
    : Triangle(height, width)
    , m_wallLength(sqrt(m_height * m_height + (m_width / 2) * (m_width / 2))) 
{}

double IsoscelesTriangle::perimeter() const
{
    return m_wallLength * 2 + m_width; 
}

EquilateralTriangle::EquilateralTriangle(double width)
    : Triangle(sqrt(width * width - (width / 2) * (width / 2)), width) {}

double EquilateralTriangle::area() const
{
    return (sqrt(3) / 4) * m_width * m_width;
}

double EquilateralTriangle::perimeter() const
{
    return 3 * m_width;
}

Quadrilateral::Quadrilateral(double height, double width)
    : m_height(height)
    , m_width(width)
{}

double Quadrilateral::area() const
{
    return m_height * m_width;
}

double Quadrilateral::perimeter() const
{
    return 2 * m_height + 2 * m_width;
}

Rectangle::Rectangle(double height, double width)
    : Quadrilateral(height, width)
{}


Square::Square(double edgeLength)
    : Rectangle(edgeLength, edgeLength)
{}

Pentagon::Pentagon(double radius)
    : m_sideLength(2 * sin(Pi / 5) * radius) // source wikipedia
{}

double Pentagon::area() const
{
    return m_sideLength * m_sideLength * 1.25 * sqrt((5 + sqrt(5)) / 2); // source wikipedia
}

double Pentagon::perimeter() const
{
    return 5 * m_sideLength;
}

Hexagon::Hexagon(double radius)
    : m_sideLength(radius) // source wikipedia
{}

double Hexagon::area() const
{
    return m_sideLength * m_sideLength * ((sqrt(3) * 3) / 2); // source wikipedia
}

double Hexagon::perimeter() const
{
    return 6 * m_sideLength;
}

Octagon::Octagon(double radius)
    : m_sideLength(radius / (sqrt(4 + 2 * sqrt(2)) / 2))
{}

double Octagon::area() const
{
    return 2 * (1 + sqrt(2)) * m_sideLength * m_sideLength;
}

double Octagon::perimeter() const
{
    return 8 * m_sideLength;
}

shared_ptr<Polygon> inputPolygon(istream& ins, ostream& outs)
{
    vector<string> shapes = {"Triangle", "IsoscelesTriangle", "EquilateralTriangle", 
        "Quadrilateral", "Square", "Rectangle", "Pentagon", "Hexagon", "Octagon"};

    outs << "What type of polygon would you like to input?" << endl;
    for (const auto& shape : shapes)
    {
        outs << shape << endl;
    }
    outs << "    :";

    string userInput;
    ins >> userInput;

    outs << "You entered " << userInput << endl;
    for (auto& c : userInput)
    {
        c = tolower(c);
    }

    for (auto& shape : shapes)
    {
        for (auto& c : shape)
        {
            c = tolower(c);
        }
    }

    if (none_of(shapes.begin(), shapes.end(), [&userInput](auto shape){
        return shape.find(userInput) != string::npos; }))
    {
        outs << "Could not recognize the polygon type " << userInput << endl;
        return nullptr;
    }

    if (userInput.find("triangle") != string::npos)
    {
        shared_ptr<Triangle> triangle = nullptr;

        if (userInput.find("equilateral") != string::npos)
        {
            double width{};
            outs << "Enter the width" << endl << "    :";
            ins >> width;
            return make_shared<EquilateralTriangle>(width);
        }
        else
        {
            double height{};
            double width{};
            outs << "Enter the height and width" << endl << "    :";
            ins >> height >> width;

            if (userInput.find("isosceles") != string::npos)
            {
                return make_shared<IsoscelesTriangle>(height, width);
            }
            else
            {
                return make_shared<Triangle>(height, width);
            }
        }
    }

    if (userInput.find("quadrilateral") != string::npos
        || userInput.find("square") != string::npos
        || userInput.find("rectangle") != string::npos)
    {
        if (userInput.find("square") != string::npos)
        {
            double edgeLength{};
            outs << "Enter the base width" << endl << "    :";
            ins >> edgeLength;
            return make_shared<Square>(edgeLength);
        }

        double height{};
        double width{};

        outs << "Enter the height and width" << endl << "    :";
        ins >> height >> width;

        if (userInput.find("rectangle") != string::npos)
        {
            return make_shared<Rectangle>(height, width);
        }
        return make_shared<Quadrilateral>(height, width);
    }

    double radius{};
    outs << "Enter the radius of the enclosing circle" << endl << "    :";
    ins >> radius;

    if (userInput.find("pentagon") != string::npos)
    {
        return make_shared<Pentagon>(radius);
    }
    if (userInput.find("hexagon") != string::npos)
    {
        return make_shared<Hexagon>(radius);
    }
    if (userInput.find("octagon") != string::npos)
    {
        return make_shared<Octagon>(radius);
    }

    return nullptr;
}

void inputPolygonWrapper(istream& ins, ostream& outs)
{
    auto polygon = inputPolygon(ins, outs);
    if (polygon)
    {
        outs << "The area is " << setprecision(4) << polygon->area() << ", and the perimeter is " << setprecision(4) << polygon->perimeter() << endl;
    }
}

string polygonSimilarity(const vector<Vertex>& polygonA, const vector<Vertex>& polygonB)
{
    stringstream result;
    auto distinctPointsA = distinctPoints(polygonA);
    auto distinctPointsB = distinctPoints(polygonB);

    if (distinctPointsA.first < 2 || distinctPointsA.second < 2 
        || distinctPointsB.first < 2 || distinctPointsB.second < 2)
    {
        result << "One or both input polygons invalid" << endl;
        return result.str();
    }

    if (polygonA.size() != polygonB.size())
    {
        result << "The two polygons are not the same shape" << endl;
        return result.str();
    }

    if (isTriangle(polygonA) && isTriangle(polygonB))
    {
        result << "the polygons are both Triangles" << endl;

        if (isIsoscelesTriangle(polygonA), isIsoscelesTriangle(polygonB))
        {
            result << "the polygons are both Isosceles Triangles" << endl;
        }

        if (isEquilateralTriangle(polygonA), isEquilateralTriangle(polygonB))
        {
            result << "the polygons are both Equilateral Triangles" << endl;
        }
    }

    if (isQuadrilateral(polygonA) && isQuadrilateral(polygonB))
    {
        result << "the polygons are both Quadrilaterals" << endl;
        
        if (isRectangle(polygonA) && isRectangle(polygonB))
        {
            result << "the polygons are both Rectangles" << endl;

            if (isSquare(polygonA) && isSquare(polygonB))
            {
                result << "the polygons are both Squares" << endl;
            }
        }
    }

    if (isPentagon(polygonA) && isPentagon(polygonB))
    {
        result << "the polygons are both Pentagons" << endl;
    }

    if (isHexagon(polygonA) && isHexagon(polygonB))
    {
        result << "the polygons are both Hexagons" << endl;
    }

    if (isOctagon(polygonA) && isOctagon(polygonB))
    {
        result << "the polygons are both Octagons" << endl;
    }

    return result.str();
}

map<char, size_t> textFileCharacterCount(const string& filepath)
{
    string word;
    ifstream inputFile(filepath);
    map<char, size_t> characterCount;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (auto c : alphabet)
    {
        characterCount[c] = 0;
    }

    if (inputFile.is_open())
    {
        while (inputFile >> word)
        {
            for (auto c : word)
            {
                c = tolower(c);
                if (alphabet.find(c) != string::npos)
                {
                    characterCount[c]++;
                }    
            } 
        }
        inputFile.close();
    }
    else {
        throw runtime_error("failed to open file");
    }

    return characterCount;
}

void printBarChart(const map<char, size_t>& characterCount)
{
    for (const auto& item : characterCount)
    {
        cout << item.first << ": ";
        for (auto i=0u; i < item.second; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
}

map<string, size_t> wordCount(const string& listOfWords)
{
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    map<string, size_t> result;
    stringstream strStream(listOfWords);

    string word;
    while(strStream >> word)
    {
        // remove punctuation and make all lower case
        string formatted;
        for (auto c : word)
        {
            c = tolower(c);
            if (alphabet.find(c) != string::npos)
            {
                formatted += c;
            }
        }
        result[formatted]++;
    }

    return result;
}
