#include "chapter1.h"
#include "mock_steady_clock.h"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using namespace chapter_1;
using namespace std;
using namespace std::chrono;
using namespace testing;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// R-1.2
TEST(FindSmallestAndLargestTest, FindsSmallestAndLargest)
{
    vector<int> sampleArray = {6, -1, -2, 3, 4, 5};
    int smallest{};
    int largest{};

    findSmallestAndLargest(sampleArray, smallest, largest);

    EXPECT_EQ(smallest, -2);
    EXPECT_EQ(largest, 6);
}

TEST(FindSmallestAndLargestTest, DoesntThrowIfEmpty)
{
    int smallest{};
    int largest{};

    vector<int> emptyVector{};
    ASSERT_NO_THROW(findSmallestAndLargest(emptyVector, smallest, largest));
}

TEST(FindSmallestAndLargestTest, OnlyOneInVector)
{
    int smallest{};
    int largest{};

    vector<int> hasOne {-1};

    findSmallestAndLargest(hasOne, smallest, largest);
    EXPECT_EQ(smallest, -1);
    EXPECT_EQ(smallest, -1);
}

// R-1.3
TEST(PairStructTest, InitToZero)
{
    chapter_1::Pair p;
    EXPECT_EQ(p.first, 0);
    EXPECT_EQ(p.second, 0.0);
}

// R-1.4
TEST(StringContents, CheckResult)
{
    string s = "abc";
    string t = "cde";

    s += s + t[1] + s;

    EXPECT_EQ(s, "abcabcdabc");
}


// R-1.5
TEST(OperatorPrecedence, OperatorPrecedence)
{
    double y = 3;
    double z = 4;
    double w = 5;

    auto result = y + 2 * z ++ < 3 - w / 5;
    auto resultWithParen = (y + (2 * (z ++))) < (3 - (w / 5));

    EXPECT_EQ(result, resultWithParen);
}

// R-1.6
TEST(AllocateArray, ProperStorage)
{
    double* dp[10];
    for (auto& i : dp)
    {
        i = new double{0.0};
    }

    for (auto i : dp)
    {
        EXPECT_EQ(*i, 0.0);
    }
}

// R-1.7
TEST(SumOfIntsSmaller, SimpleMathCheck)
{
    auto n = 4u;
    auto expectedResult = 1ul + 2ul + 3ul;

    EXPECT_EQ(sumOfIntsSmaller(n), expectedResult);
}

TEST(SumOfIntsSmaller, MaxArgResultGreater)
{
    auto n = std::numeric_limits<uint32_t>::max();
    auto result = sumOfIntsSmaller(n);
    EXPECT_GT(result, n);
}

// R-1.8
TEST(IsMultiple, IsMultiple)
{
    EXPECT_TRUE(isMultiple(20, 5));
    EXPECT_TRUE(isMultiple(2, 1));
    EXPECT_TRUE(isMultiple(6, 2));
    EXPECT_TRUE(isMultiple(18, 3));
    EXPECT_TRUE(isMultiple(66, 11));

    EXPECT_FALSE(isMultiple(15, 10));
    EXPECT_FALSE(isMultiple(5, 4));
    EXPECT_FALSE(isMultiple(5, 10));
}

TEST(IsMultiple, EdgeCases)
{
    EXPECT_NO_THROW(EXPECT_TRUE(isMultiple(0, 0)));
    EXPECT_NO_THROW(EXPECT_TRUE(isMultiple(0, 10)));
    EXPECT_NO_THROW(EXPECT_FALSE(isMultiple(7, 0)));
}

// R-1.9
TEST(PrintArray, PrintArray)
{
    int** A = nullptr;
    constexpr auto m = 4;
    constexpr auto n = 6;

    A = new int*[m];
    for(auto row=0; row < m; ++row)
    {
        *(A + row) = new int[n];
        auto rowPtr = *(A + row);
        for (auto index=0; index<n; ++index)
        {
            rowPtr[index] = (row * n) + index;
        }
    }

    printArray(A, m, n);
}

// R-1.11
TEST(FlowerClass, ConstructorSetsMembers)
{
    constexpr auto name = "Daisy";
    constexpr auto numPedals = 12;
    constexpr auto price = 9.99f;

    Flower f(name, numPedals, price);
    EXPECT_EQ(f.getName(), name);
    EXPECT_EQ(f.getNumPedals(), numPedals);
    EXPECT_EQ(f.getPrice(), price);
}

TEST(FlowerClass, SetMembers)
{
    constexpr auto name = "Daisy";
    constexpr auto numPedals = 12;
    constexpr auto price = 9.99f;

    Flower f("no name", 0, 0.f);
    f.setName(name);
    f.setNumPedals(numPedals);
    f.setPrice(price);

    EXPECT_EQ(f.getName(), name);
    EXPECT_EQ(f.getNumPedals(), numPedals);
    EXPECT_EQ(f.getPrice(), price);
}

class CreditCardTest : public Test {
public:
    CreditCardTest()
    {
        ON_CALL(*m_mockClock, now()).WillByDefault(Invoke([&]() {
            return m_currentTime; }));
    }

    unique_ptr<CreditCard> makeCreditCard(string no, string nm, int lim, double bal=0)
    {
        return make_unique<CreditCard>(m_mockClock, no, nm, lim, bal);
    }

    shared_ptr<MockSteadyClock> m_mockClock = make_shared<NiceMock<MockSteadyClock>>();
    steady_clock::time_point m_currentTime{};
};

// R-1.12
TEST_F(CreditCardTest, ChargeItRejectsNegative)
{
    auto c = makeCreditCard("12132343", "eric", 1000);

    EXPECT_FALSE(c->chargeIt(-20.00));
}

TEST_F(CreditCardTest, NegativePaymentNoEffect)
{
    auto c = makeCreditCard("12132343", "eric", 1000);

    c->chargeIt(20.00);
    c->makePayment(-10.00);
    EXPECT_EQ(c->getBalance(), 20.00);
}

// R-1.13
TEST_F(CreditCardTest, ChargesInterestOnPayments)
{
    auto c = makeCreditCard("12132343", "eric", 1000);
    c->chargeIt(10000.00);

    auto payment = 20.00;
    auto balance = c->getBalance();
    c->makePayment(payment);

    EXPECT_LT(balance - c->getBalance(), payment);
}

TEST_F(CreditCardTest, InterestProportionalToPayment)
{
    auto c = makeCreditCard("12132343", "eric", 1000);
    c->chargeIt(10000.00);

    auto payment = 20.00;
    auto balance = c->getBalance();
    c->makePayment(payment);

    auto amountOfInterest = payment - (balance - c->getBalance());

    payment *= 2;

    balance = c->getBalance();
    c->makePayment(payment);

    auto moreInterest = payment - (balance - c->getBalance());

    EXPECT_GT(moreInterest, amountOfInterest);
}

// R-1.14
TEST_F(CreditCardTest, LatePaymentFee)
{
    auto cardPayedLate = makeCreditCard("12132343", "eric", 1000);
    auto charge = 20.00;
    cardPayedLate->chargeIt(charge);

    m_currentTime += 720h + 1h;
    cardPayedLate->makePayment(charge);
    auto latePayBalance = cardPayedLate->getBalance();

    auto cardPayedEarly = makeCreditCard("11111111", "tim", 1000);
    cardPayedEarly->chargeIt(charge);

    m_currentTime += 1h;
    cardPayedEarly->makePayment(charge);
    auto earlyPayBalance = cardPayedEarly->getBalance();

    EXPECT_THAT(earlyPayBalance, Lt(latePayBalance));
}