#include "chapter2.h"

#include <gmock/gmock.h>

#include <array>
#include <numeric>

using namespace std;
using namespace testing;

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
