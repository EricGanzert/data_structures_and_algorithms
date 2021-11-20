#include "chapter1.h"
#include "mock_steady_clock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <unordered_set>
#include <numeric>
#include <vector>

using namespace std;
using namespace std::chrono;
using namespace testing;

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
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
    MyPair p;
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

// R-1.15
TEST_F(CreditCardTest, SetNumber)
{
    auto card = makeCreditCard("12132343", "eric", 1000);
    constexpr auto NewNumber = "new number";
    card->setNumber(NewNumber);
    EXPECT_THAT(card->getNumber(), Eq(NewNumber));
}

TEST_F(CreditCardTest, SetName)
{
    auto card = makeCreditCard("12132343", "eric", 1000);
    constexpr auto NewName = "new name";
    card->setName(NewName);
    EXPECT_THAT(card->getName(), Eq(NewName));
}

TEST_F(CreditCardTest, BalanceZeroByDefault)
{
    auto card = makeCreditCard("12132343", "eric", 1000);
    EXPECT_THAT(card->getBalance(), Eq(0.00));
}

TEST_F(CreditCardTest, BalanceCanHaveFractionalComponent)
{
    constexpr auto OriginalBalance = 0.01;
    auto card = makeCreditCard("12132343", "eric", 1000, OriginalBalance);
    EXPECT_THAT(card->getBalance(), Gt(0.00));
}

TEST_F(CreditCardTest, SetBalanceNegativeRejected)
{
    constexpr auto OriginalBalance = 20.00;
    auto card = makeCreditCard("12132343", "eric", 1000, OriginalBalance);
    
    card->setBalance(-12);
    EXPECT_THAT(card->getBalance(), Eq(OriginalBalance));
}


TEST_F(CreditCardTest, SetBalance)
{
    auto card = makeCreditCard("12132343", "eric", 1000);

    constexpr auto NewBalance = 33.00;
    card->setBalance(NewBalance);

    EXPECT_THAT(card->getBalance(), Eq(NewBalance));
}

// R-1.16
TEST_F(CreditCardTest, Fragment1_4)
{
    vector<unique_ptr<CreditCard>> wallet(10);

    wallet[0] = makeCreditCard("5391 0375 9387 5309", "John Bowman", 2500);
    wallet[1] = makeCreditCard("3485 0399 3395 1954", "John Bowman", 3500);
    wallet[2] = makeCreditCard("6011 4902 3294 2994", "John Bowman", 5000);

    for (int j=1; j <= 58; j++)
    {
        wallet[0]->chargeIt(double(j));
        wallet[1]->chargeIt(2 * j);
        wallet[2]->chargeIt(double(3 * j));
    }

    cout << "Card payments:" << endl;
    for (int i=0; i < 3; i++)
    {
        cout << *wallet[i];
        while (wallet[i]->getBalance() > 100.0)
        {
            wallet[i]->makePayment(100.0);
        }
        cout << "New balance = " << wallet[i]->getBalance() << endl;
        cout << endl;
    }
}

// R-1.17
TEST(AllKindsTest, DefaultConstructorZeroes)
{
    AllKinds ak;

    EXPECT_THAT(ak.getInt(), Eq(int(0)));
    EXPECT_THAT(ak.getLongInt(), Eq(long(0)));
    EXPECT_THAT(ak.getFloat(), Eq(0.f));
}

TEST(AllKindsTest, SetAndGetFunctions)
{
    AllKinds ak;

    ak.setInt(1);
    EXPECT_THAT(ak.getInt(), Eq(int(1)));

    ak.setLongInt(2);
    EXPECT_THAT(ak.getLongInt(), Eq(long(2)));

    ak.setFloat(3.f);
    EXPECT_THAT(ak.getFloat(), Eq(3.f));
}

TEST(AllKindsTest, ConstructorSetsMembers)
{
    AllKinds ak(5, 6l, 7.f);
    EXPECT_THAT(ak.getInt(), Eq(int(5)));
    EXPECT_THAT(ak.getLongInt(), Eq(long(6)));
    EXPECT_THAT(ak.getFloat(), Eq(7.f));
}

TEST(AllKindsTest, SumOfAllCombos)
{
    AllKinds ak(5, 6l, 7.f);

    double expectedResult = 5 * 6l + 5 * 7.f + 6l * 7.f;
    EXPECT_THAT(ak.sumOfAllCombos(), Eq(expectedResult));
}

// R-1.18
TEST(IsMultiple, NegativeInputs)
{
    EXPECT_TRUE(isMultiple(-20, 5));
    EXPECT_TRUE(isMultiple(20, -5));
    EXPECT_TRUE(isMultiple(-20, -5));

    EXPECT_FALSE(isMultiple(-13, 4));
}

// R-1.19
TEST(TwoPower, TwoPower)
{
    EXPECT_TRUE(twoPower(1));
    EXPECT_TRUE(twoPower(2));
    EXPECT_TRUE(twoPower(4));
    EXPECT_TRUE(twoPower(16));
    EXPECT_TRUE(twoPower(128));
    EXPECT_TRUE(twoPower(1024));

    EXPECT_FALSE(twoPower(0));
    EXPECT_FALSE(twoPower(-2));
    EXPECT_FALSE(twoPower(3));
    EXPECT_FALSE(twoPower(31));
    EXPECT_FALSE(twoPower(33));
}

// R-1.21
TEST(SumOfOddIntsSmaller, SumOfOddIntsSmaller)
{
    EXPECT_EQ(sumOfOddIntsSmaller(4), 4);
    EXPECT_EQ(sumOfOddIntsSmaller(10), 25);
    EXPECT_EQ(sumOfOddIntsSmaller(13), 36);
}

// R-1.22
TEST(NumDividesBy2Above2, NumDividesBy2Above2)
{
    EXPECT_EQ(numDividesBy2Above2(64), 5);
    EXPECT_EQ(numDividesBy2Above2(33.3), 4);
    EXPECT_EQ(numDividesBy2Above2(29.9), 3);

    EXPECT_EQ(numDividesBy2Above2(-64), 0);
}

// C-1.1
TEST(ReveseArray, ReverseArray)
{
    constexpr auto Iterations = 10U;

    vector<int> testArray{1, 2, 3, 4, 5};
    vector<int> arrayReversed{5, 4, 3, 2, 1};

    for (auto i=0U; i<Iterations; i++)
    {
        testArray.clear();
        arrayReversed.clear();

        for (auto item=0U; item<i; item++)
        {
            testArray.emplace_back(item);
            arrayReversed.emplace_back(i - (item + 1));
        }

        vector<int> result;
        EXPECT_NO_THROW(result = reverseArray(testArray));

        EXPECT_EQ(result, arrayReversed);
    }
}

// C-1.2
TEST(ContainsEvenProduct, ContainsEvenProduct)
{
    vector<int> testArray{1, 2};
    EXPECT_TRUE(containsEvenProductOfPair(testArray));

    testArray = {1, 3};
    EXPECT_FALSE(containsEvenProductOfPair(testArray));

    testArray = {1, 3, 2};
    EXPECT_TRUE(containsEvenProductOfPair(testArray));

    testArray = {2};
    EXPECT_FALSE(containsEvenProductOfPair(testArray));

    testArray.clear();
    EXPECT_FALSE(containsEvenProductOfPair(testArray));
}

// C-1.3
TEST(AllUnique, AllUnique)
{
    EXPECT_TRUE(allVectorElementsUnique(vector<int>()));

    vector<int> testArray{1, 2};
    EXPECT_TRUE(allVectorElementsUnique(testArray));

    testArray = {1, 1};
    EXPECT_FALSE(allVectorElementsUnique(testArray));

    testArray = {1, 2, 2};
    EXPECT_FALSE(allVectorElementsUnique(testArray));

    testArray = {1, 2, 3, 4, 5};
    EXPECT_TRUE(allVectorElementsUnique(testArray));

    testArray = {1, 2, 3, 4, 3};
    EXPECT_FALSE(allVectorElementsUnique(testArray));
}

// C-1.4
TEST(PrintOdds, PrintOdds)
{
    stringstream outs;
    vector<int> testArray{1, 2, 3, 4, 5};
    printOdds(outs, testArray);

    auto result = outs.str();
    EXPECT_THAT(result.find("1"), Ne(string::npos));
    EXPECT_THAT(result.find("2"), Eq(string::npos));
    EXPECT_THAT(result.find("3"), Ne(string::npos));
    EXPECT_THAT(result.find("4"), Eq(string::npos));
    EXPECT_THAT(result.find("5"), Ne(string::npos));
}

// C-1.5
TEST(ShuffleInts, ShuffleInts)
{
    auto printArray = [](const vector<int>& arg)
    {
        for (const auto& item : arg)
        {
            cout << item << " "; 
        }
        cout << endl;
    };

    constexpr auto ArraySize = 52;
    vector<int> myArray(ArraySize);
    iota(myArray.begin(), myArray.end(), 1);

    auto beforeShuffling = myArray;
    unordered_set<int> beforeShuffleLookup(myArray.begin(), myArray.end());

    cout << "array before shuffling: ";
    printArray(myArray);
    shuffleArray(myArray);
    cout << endl << "array after shuffling: ";
    printArray(myArray);
    cout << endl;

    ASSERT_THAT(myArray.size(), Eq(ArraySize));

    // Every card must be accounted for
    for (const auto& item : myArray)
    {
        EXPECT_THAT(beforeShuffleLookup.count(item), Eq(1u));
    }

    // Can't be in the same order
    EXPECT_THAT(myArray, Ne(beforeShuffling));
}

// C-1.6
TEST(CombineLetters, CombineLetters)
{
    function<int(int)> factorial = [&](int n)
    {
        return (n == 0) || (n == 1) ? 1 : n * factorial(n - 1);
    };

    stringstream outs;
    const string abcdef = "abcdef";
    allPossibleStrings(outs, abcdef);
    const auto result = outs.str();

    const auto expectedNumWords = factorial(abcdef.size());
    auto resultWordCount = 0l;
    unordered_set<string> seen;

    stringstream countTool(result);
    string aWord;
    while(countTool >> aWord) 
    {
        EXPECT_THAT(aWord.size(), Eq(abcdef.size()));
        for (char x : abcdef)
        {
            // assert rather than expect to avoid too much error output if something is wrong
            ASSERT_TRUE(aWord.find(x) != string::npos);
        }
        
        ASSERT_FALSE(seen.count(aWord));
        seen.insert(aWord);
        resultWordCount++;
    }

    EXPECT_THAT(resultWordCount, Eq(expectedNumWords));
}

// C-1.7
TEST(ReverseLines, ReverseLines)
{
    vector<string> allLines = {"this is a line", "another line", "last line now, goodbye"};
    string forward;
    for (const auto& line : allLines)
    {
        forward += line + "\n";
    }
    string reverse;
    for (auto line = allLines.rbegin(); line != allLines.rend(); line++)
    {
        reverse += *line + "\n";
    }

    istringstream inputStream(forward);
    stringstream outputStream;
    reverseLines(inputStream, outputStream);

    EXPECT_THAT(outputStream.str(), Eq(reverse));
}

// C-1.8
TEST(ElementWiseProduct, DifferentSizedInputsThrowsException)
{
    vector<int> a(3);
    vector<int> b(2);

    EXPECT_THROW(elementWiseProduct(a, b), runtime_error);
}

TEST(ElementWiseProduct, SameSizedInputsNoThrow)
{
    vector<int> a(3);
    vector<int> b(3);

    EXPECT_NO_THROW(elementWiseProduct(a, b));
}

TEST(ElementWiseProduct, ResultIsCorrectSize)
{
    vector<int> a = {1, 2, 3};
    vector<int> b = {4, 5, 6};

    auto result = elementWiseProduct(a, b);
    EXPECT_THAT(result.size(), Eq(3));
}

TEST(ElementWiseProduct, ResultIsCorrect)
{
    vector<int> a = {1, 2, 3};
    vector<int> b = {4, 5, 6};
    vector<int> expectedResult = {4, 10, 18};

    auto result = elementWiseProduct(a, b);
    EXPECT_THAT(result, Eq(expectedResult));
}

// C-1.9
TEST(Vector2, addVectors)
{
    Vector2 v1(-1, 1);
    Vector2 v2(4, 4);
    Vector2 expectedSum(3, 5);

    auto summed = v1 + v2;
    EXPECT_THAT(summed, Eq(expectedSum));
}

TEST(Vector2, MultiplyVectorByScalar)
{
    Vector2 v1(-3, 3);
    auto product = v1 * 4;
    Vector2 expectedProduct(-12, 12);

    EXPECT_THAT(product, Eq(expectedProduct));
}

TEST(Vector2, DotProduct)
{
    Vector2 v1(-2, 5);
    Vector2 v2(3, 1);
    double expectedProduct = -1;

    auto product = dotProduct(v1, v2);
    EXPECT_THAT(product, Eq(expectedProduct));
}

// C-1.10
TEST(PowerOf2, PowerOf2)
{
    EXPECT_THAT(powerOf2(0), Eq(1ul));
    EXPECT_THAT(powerOf2(1), Eq(2ul));
    EXPECT_THAT(powerOf2(2), Eq(4ul));
    EXPECT_THAT(powerOf2(3), Eq(8ul));
}

// C-1.11
TEST(GreatestCommonDivisor, PositiveNumbers)
{
    EXPECT_THAT(gcd(0, 0), 0);
    EXPECT_THAT(gcd(1, 0), 0);
    EXPECT_THAT(gcd(1, 1), 1);
    EXPECT_THAT(gcd(2, 1), 1);
    EXPECT_THAT(gcd(4, 2), 2);
    EXPECT_THAT(gcd(15, 3), 3);
    EXPECT_THAT(gcd(13, 2), 1);
    EXPECT_THAT(gcd(80844, 25320), 12);
}

TEST(GreatestCommonDivisor, NumbersReversed)
{
    EXPECT_THAT(gcd(25320, 80844), 12);
}

TEST(GreatestCommonDivisor, NegativeNumbers)
{
    EXPECT_THAT(gcd(-15, 3), 3);
    EXPECT_THAT(gcd(15, -3), 3);
    EXPECT_THAT(gcd(-15, -3), 3);
}

// P-1.3
TEST(BirthdayParadox, BirthdayParadox)
{
    array<uint32_t, 20> numPeople{};
    for (auto i=0u; i<20u; i++)
    {
        numPeople[i] = (i + 1) * 5;
    }

    for (const auto& n : numPeople)
    {
        auto numMatches = 0u;
        for (auto test=1u; test<=10u; test++)
        {
            numMatches += static_cast<decltype(numMatches)>(sharedBirthday(n));
        }
        cout << "For a group of " << n << " people, in " << numMatches << 
            " out of 10 tests there were matching birthdays" << endl;
    }
}
