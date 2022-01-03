#include "chapter2.h"

#include <gmock/gmock.h>

#include <array>
#include <chrono>
#include <numeric>

using namespace money;
using namespace std;
using namespace std::chrono;
using namespace testing;

namespace
{
// Without using mocks for InternetUser I don't see a better way
// than using a timeout
constexpr auto PacketTripTimeout = 50ms;

bool doubleEq(double a, double b, double tolerance = 0.000001)
{
    return fabs(a - b) < tolerance;
}

constexpr auto Pi = 3.14159265;
}

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// R-2.8
TEST(Fibbonacci, SeventhValueFrom3and4)
{
    stringstream outs;
    FibonacciProgression fib(outs, 3, 4);
    fib.printProgression(7);

    auto result = outs.str();
    EXPECT_THAT(result, Eq(string("3 4 7 11 18 29 47\n")));
}

// R-2.9
TEST(ArithmeticOverflow, ArithmeticOverflow)
{
    // I'm not sure how I should test this. Because nextValue is protected and
    // the string produced by printProgression would be unreasonably large
    auto maxValue = numeric_limits<long>::max();
    auto result = maxValue / 128;
    if (maxValue % 128 == 0)
    {
        result--;
    }
    
    cout << "If we chose inc=128, we could call ArithProgression::nextValue "
        << result << " times before we cause long integer overflow." << endl;
}

// R-2.13
TEST(PerformArrayReference, OutOfBounds)
{
    // It looks like trying to access an array out of bounds 
    // is undefined behaviour and may not on some platforms
    // throw exceptions. In any case gmock doesn't seem to like it
    // when I try to catch an exception from an out of bounds reference
    try
    {
        throw(runtime_error("test exception"));
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
}

// R-2.14
TEST(ClassPointerCasting, WhatIsOutput)
{
    shared_ptr<Region> mid = make_shared<State>();
    shared_ptr<State> md = make_shared<MaryLand>();
    shared_ptr<Object> obj = make_shared<Place>();
    shared_ptr<Place> usa = make_shared<Region>();

    md->printMe(); // Read it.
    mid->printMe(); // Ship it.

    if (auto ptr = dynamic_cast<Place*>(obj.get()))
    {
        ptr->printMe(); // Buy it.
    }

    obj = md;
    if (auto ptr = dynamic_cast<MaryLand*>(obj.get()))
    {
        ptr->printMe(); // Read it.
    }

    obj = usa;
    if (auto ptr = dynamic_cast<Place*>(obj.get()))
    {
        ptr->printMe(); // Box it.
    }

    usa = md;
    if (auto ptr = dynamic_cast<Place*>(usa.get()))
    {
        ptr->printMe(); // Read it.
    }
}

// R-2.15
TEST(CountVowels, NoVowel)
{
    EXPECT_THAT(countVowels("bcdfgh"), size_t(0));
}

TEST(CountVowels, LowerCase)
{
    EXPECT_THAT(countVowels("eric"), size_t(2));
}

TEST(CountVowels, UpperCase)
{
    EXPECT_THAT(countVowels("ERIC"), size_t(2));
}

TEST(CountVowels, MixedCase)
{
    EXPECT_THAT(countVowels("ERic"), size_t(2));
}

TEST(CountVowels, MultipleWords)
{
    EXPECT_THAT(countVowels("time for lunch"), size_t(4));
}

TEST(CountVowels, VowelIsY)
{
    EXPECT_THAT(countVowels("fly"), size_t(1));
}

TEST(CountVowels, OnlyCountYifNoOtherVowels)
{
    EXPECT_THAT(countVowels("mary"), size_t(1));
}

// R-2.16
TEST(RemovePunctuation, ExampleString)
{
    string input = "Let's try, Mike.";
    removePunctuation(input);
    EXPECT_THAT(input, Eq(string("Lets try Mike")));
}

// R-2.17
TEST(ArithmeticOperatores, DivideByZeroSafe)
{
    bool result{};
    EXPECT_NO_THROW(result = correctArithmeticFormula(3, 0, 1));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result = correctArithmeticFormula(3, 1, 0));
    EXPECT_FALSE(result);
}

TEST(ArithmeticOperatores, ShouldBeTrue)
{
    EXPECT_TRUE(correctArithmeticFormula(1, 7, 8)); // a + b == c
    EXPECT_TRUE(correctArithmeticFormula(8, 1, 7)); // a - b == c
    EXPECT_TRUE(correctArithmeticFormula(3, 2, 6)); // a * b == c
    EXPECT_TRUE(correctArithmeticFormula(6, 2, 3)); // a / b == c

    EXPECT_TRUE(correctArithmeticFormula(8, 7, 1)); // a == b + c
    EXPECT_TRUE(correctArithmeticFormula(7, 8, 1)); // a == b - c
    EXPECT_TRUE(correctArithmeticFormula(6, 2, 3)); // a == b * c
    EXPECT_TRUE(correctArithmeticFormula(3, 6, 2)); // a == b / c
}

TEST(ArithmeticOperatores, ShouldBeFalse)
{
    EXPECT_FALSE(correctArithmeticFormula(1, 5, 10));
}

// R-2.18
TEST(PairClass, PairClass)
{
    MyPair<int, string> pair1(12, "Hello");
    MyPair<float, long> pair2(1.1f, 1000l);
    MyPair<uint8_t, uint64_t> pair3(0xff, 0xffffffff);
    MyPair<string, string> pair4("One", "Another");
    MyPair<MyPair<int, string>, string> pair5(pair1, "Last one");
}

// C-2.4
TEST(LineIntersect, ParallelLinesThrow)
{
    EXPECT_THROW(Line(2, 1).intersect(Line(2, 2)), runtime_error);
}

TEST(LineIntersect, NonParallelNoThrow)
{
    EXPECT_NO_THROW(Line(2, 1).intersect(Line(3, 4)));
}

TEST(LineIntersect, IntersctionPoint)
{
    auto intersect = Line(2, 1).intersect(Line(1, 2));
    EXPECT_DOUBLE_EQ(intersect, 1.0);

    intersect = Line(3, -5).intersect(Line(12, 1.11));
    auto expectedAnswer = (1.11 + 5.0) / (3.0 - 12.0);
    EXPECT_DOUBLE_EQ(intersect, expectedAnswer);

    try
    {
        Line(2, 1).intersect(Line(2, 2));
    }
    catch(exception& e)
    {
        cout << "Failed to find intersection point - " << e.what() << endl;
    }
}

// C-2.5
TEST(AbsDiffProgression, AbsDiffProgression)
{
    stringstream outs;
    AbsDifference absDiff(outs);
    absDiff.printProgression(10);

    auto result = outs.str();
    EXPECT_EQ(result, string("2 200 198 2 196 194 2 192 190 2\n"));
}

// C-2.6
TEST(SqrtProgression, SqrtProgression)
{
    stringstream outs;
    SqrtProgression sqrtProg(outs);
    sqrtProg.printProgression(4);

    auto result = outs.str();
    EXPECT_EQ(result, string("65536 256 16 4\n"));
}

// C-2.7
TEST(BaseClassMember, BaseClassMember)
{
    C myClass;
    EXPECT_THAT(myClass.getXFromBase(), 1);
    EXPECT_THAT(myClass.getX(), 3);
}

// C-2.8
TEST(InternetMockup, InternetUserWithoutInternetThrows)
{
    EXPECT_THROW(InternetUser("Steve", nullptr), runtime_error);
}

TEST(InternetMockup, AliceSendsPacketToBob)
{
    constexpr Packet TestPacket = 12345;
    auto internet = make_shared<Internet>();
    auto alice = make_shared<InternetUser>("Alice", internet);
    auto bob = make_shared<InternetUser>("Bob", internet);

    auto startTime = steady_clock::now();
    alice->sendPacket(Packet(TestPacket), bob);

    bool received = false;
    while ((steady_clock::now() - startTime) < PacketTripTimeout)
    {
        if (bob->numPacketsProcessed())
        {
            EXPECT_THAT(bob->lastPacketProcessed(), TestPacket);
            received = true;
            break;
        }
    }

    EXPECT_TRUE(received);
}

TEST(InternetMockup, Timing10000Packets)
{
    constexpr int NumPackets = 10000;
    Packet testPacket = 0;
    auto internet = make_shared<Internet>();
    auto alice = make_shared<InternetUser>("Alice", internet);
    auto bob = make_shared<InternetUser>("Bob", internet);

    auto startTime = steady_clock::now();
    for (auto i=0; i<NumPackets; ++i)
    {
        alice->sendPacket(testPacket++, bob);
    }

    // make sure the packet gets to Bob
    bool finished = false;
    while ((steady_clock::now() - startTime) < PacketTripTimeout * NumPackets)
    {
        if (bob->numPacketsProcessed() >= NumPackets)
        {
            finished = true;
            break;
        }
    }

    EXPECT_TRUE(finished);
    auto elapsedTime = duration_cast<microseconds>(steady_clock::now() - startTime);
    cout << "It took " << elapsedTime.count() << " microseconds to pass " << NumPackets << " packets" << endl;
}

// C-2.9
TEST(Polynomial, TermPrint)
{
    stringstream ss;
    Term polynomial(2.0, 3); // 2x^3
    polynomial.print(ss);
    auto result = ss.str();
    EXPECT_EQ(result, string("+2x^3"));
}

TEST(Polynomial, TermDerive)
{
    stringstream ss;
    Term polynomial(2.0, 3); // 2x^3
    polynomial.derive();
    polynomial.print(ss);

    auto result = ss.str();
    EXPECT_EQ(result, string("+6x^2"));
}

TEST(Polynomial, ConstructAndPrint)
{
    stringstream ss;
    vector<Term> terms = {Term(2, 3), Term(4, 1), Term(1, 0)};
    Polynomial polynomial(terms, ss);

    polynomial.print();
    auto result = ss.str();
    EXPECT_EQ(result, string("+2x^3+4x^1+1x^0"));
}

TEST(Polynomial, OrdersTerms)
{
    stringstream ss;
    vector<Term> terms = {Term(4, 1), Term(2, 3), Term(1, 0)};
    Polynomial polynomial(terms, ss);

    polynomial.print();
    auto result = ss.str();
    EXPECT_EQ(result, string("+2x^3+4x^1+1x^0"));
}


TEST(Polynomial, PolynomialDerive)
{
    stringstream ss;
    // +2x^3+4x^1+1x^0
    vector<Term> terms = {Term(2, 3), Term(4, 1), Term(1, 0)};
    Polynomial polynomial(terms, ss);

    polynomial.derive();
    polynomial.print();
    auto result = ss.str();
    EXPECT_EQ(result, string("+6x^2+4x^0"));
}

// P-2.1
TEST(DivideBy2, ReturnsZeroIfArgIsTwoOrLess)
{
    EXPECT_EQ(numTimesDivideBy2(0), size_t(0));
    EXPECT_EQ(numTimesDivideBy2(1), size_t(0));
    EXPECT_EQ(numTimesDivideBy2(2), size_t(0));
}

TEST(DivideBy2, DivideBy2)
{
    EXPECT_EQ(numTimesDivideBy2(4), size_t(2));
    EXPECT_EQ(numTimesDivideBy2(15), size_t(3));
    EXPECT_EQ(numTimesDivideBy2(32), size_t(5));
}

// P-2.2
TEST(MakeChange, NoChangeIfNotEnoughGiven)
{
    const Change empty{};
    EXPECT_EQ(makeChange(200, 100), empty);
    EXPECT_EQ(makeChange(100, 100), empty);
    
}

TEST(MakeChange, MakesChange)
{
    constexpr ValueCents TenDollarBill = 1000;
    constexpr ValueCents Loonie = 100;
    constexpr ValueCents Quarter = 25;
    constexpr ValueCents Penny = 1;

    auto change = makeChange(188.24, 200);

    cout << "item costs $188.24, paid $200 so change is:" << endl;
    for (const auto& item : change)
    {
        cout << "$" << item.first / 100.0 << " x " << item.second << endl;
    }

    EXPECT_THAT(change.size(), size_t(4));

    ASSERT_THAT(change.count(TenDollarBill), size_t(1));
    EXPECT_THAT(change[TenDollarBill], size_t(1));

    ASSERT_THAT(change.count(Loonie), size_t(1));
    EXPECT_THAT(change[Loonie], size_t(1));

    ASSERT_THAT(change.count(Quarter), size_t(1));
    EXPECT_THAT(change[Quarter], size_t(3));

    ASSERT_THAT(change.count(Penny), size_t(1));
    EXPECT_THAT(change[Penny], size_t(1));    
}

// P-2.3
constexpr auto VectorSize = 5;

template<typename T>
struct VectorTest : public testing::Test
{
    using ElementType = T;

    VectorTest()
        : vecA(VectorSize)
        , vecB(VectorSize)
    {
        for (auto i=0u; i<VectorSize; i++)
        {
            vecA.at(i) = i;
            vecB.at(i) = i;
        }
    }

    Vector<ElementType> vecA;
    Vector<ElementType> vecB;
};

using MyTypes = testing::Types<int, double, Complex>;
TYPED_TEST_SUITE(VectorTest, MyTypes);

TYPED_TEST(VectorTest, Addition)
{
    auto sum = vecA + vecB;
    for (auto i=0u; i<VectorSize; i++)
    {
        EXPECT_THAT(sum.at(i), Eq(vecA.at(i) + vecB.at(i)));
    }
}

TYPED_TEST(VectorTest, Subtraction)
{
    auto diff = vecA - vecB;
    for (auto i=0u; i<VectorSize; i++)
    {
        EXPECT_THAT(diff.at(i), Eq(vecA.at(i) - vecB.at(i)));
    }
}

TYPED_TEST(VectorTest, MultiplyScalar)
{
    using ElementType  = typename TestFixture::ElementType;
    const ElementType scalar(5);

    auto product = vecA * scalar;
    for (auto i=0u; i<VectorSize; i++)
    {
        EXPECT_THAT(product.at(i), Eq(vecA.at(i) * scalar));
    }

    // reversed operator order
    product = scalar * vecA;
    for (auto i=0u; i<VectorSize; i++)
    {
        EXPECT_THAT(product.at(i), Eq(vecA.at(i) * scalar));
    }
}

TYPED_TEST(VectorTest, DotProduct)
{
    using ElementType  = typename TestFixture::ElementType;
    auto dotProduct = vecA * vecB;

    // both vectors are {0, 1, 2, 3, 4}
    // see test fixture
    EXPECT_THAT(dotProduct, Eq(ElementType(30)));
}

TEST(Complex, Add)
{
    Complex a(1, 2);
    Complex b(3, 4);
    auto sum = a + b;

    EXPECT_THAT(sum, Complex(4, 6));
}

TEST(Complex, Subtract)
{
    Complex a(1, 2);
    Complex b(3, 4);
    auto diff = a - b;

    EXPECT_THAT(diff, Complex(-2, -2));
}

TEST(Complex, Multiply)
{
    Complex a(1, 2);
    Complex b(3, 4);
    auto product = a * b;

    EXPECT_THAT(product, Complex(-5, 10));
}

// P-2.4
TEST(AnimalTest, DifferentTypesNothingHappens)
{
    shared_ptr<Animal> dog = make_shared<Dog>(true, 1.0f);
    shared_ptr<Animal> chicken = make_shared<Chicken>(false, 0.2f);

    auto result = interact(dog, chicken);

    EXPECT_THAT(dog, Not(IsNull()));
    EXPECT_THAT(chicken, Not(IsNull()));
    EXPECT_THAT(result, IsNull());
}

template<typename T>
struct AnimalTest : public testing::Test
{
    using Species = T;
};

using AnimalTypes = testing::Types<Dog, Chicken>;
TYPED_TEST_SUITE(AnimalTest, AnimalTypes);

TYPED_TEST(AnimalTest, OnlyStrongerSurvives)
{
    shared_ptr<Animal> strong = make_shared<Species>(true, 2.0f);
    shared_ptr<Animal> weak = make_shared<Species>(true, 1.0f);

    auto result = interact(strong, weak);
    
    EXPECT_THAT(strong, Not(IsNull()));
    EXPECT_THAT(weak, IsNull());
    EXPECT_THAT(result, IsNull());
}

TYPED_TEST(AnimalTest, DifferentGendersMate)
{
    shared_ptr<Animal> male = make_shared<Species>(true, 2.0f);
    shared_ptr<Animal> female = make_shared<Species>(false, 1.0f);

    auto result = interact(male, female);
    
    EXPECT_THAT(male, Not(IsNull()));
    EXPECT_THAT(female, Not(IsNull()));
    EXPECT_THAT(result, Not(IsNull()));
}

// P-2.5
TEST(Polygon, TriangleAreaPerimeter)
{
    Triangle myTriangle(5, 3);

    EXPECT_TRUE(doubleEq(myTriangle.area(), 7.5));
    EXPECT_TRUE(doubleEq(myTriangle.perimeter(), 8 + sqrt(34)));
}

TEST(Polygon, QuadrilateralAreaPerimeter)
{
    Quadrilateral myQuad(11, 4);

    EXPECT_TRUE(doubleEq(myQuad.area(), 44));
    EXPECT_TRUE(doubleEq(myQuad.perimeter(), 30));
}

TEST(Polygon, PentagonAreaPerimeter)
{
    constexpr auto Radius = 5.0;
    const auto sideLength = 2 * sin(Pi / 5) * Radius; // source wikipedia
    Pentagon myPentagon(Radius);

    auto expectedPerimeter = sideLength * 5;
    EXPECT_TRUE(doubleEq(myPentagon.perimeter(), expectedPerimeter));

    auto expectedArea = sideLength * sideLength * 1.25 * sqrt((5 + sqrt(5)) / 2); // source wikipedia
    EXPECT_TRUE(doubleEq(myPentagon.area(), expectedArea));
}

TEST(Polygon, HexagonAreaPerimeter)
{
    constexpr auto Radius = 5.0;
    Hexagon myHexagon(Radius);

    auto expectedPerimeter = 6 * Radius; // radius == side length
    EXPECT_TRUE(doubleEq(myHexagon.perimeter(), expectedPerimeter));

    auto expectedArea = Radius * Radius * ((sqrt(3) * 3) / 2); // source wikipedia
    EXPECT_TRUE(doubleEq(myHexagon.area(), expectedArea));
}