#include "chapter3.h"
#include <deque>

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

namespace {
void printMatrix(const Matrix& m)
{
    if (m.empty())
    {
        return;
    }

    for (auto i=0u; i<m.size(); i++)
    {
        for (auto j=0u; j<m.begin()->size(); j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void assertListResult(StringLinkedList& theList, deque<string>& expectedResult)
{
    ASSERT_THAT(theList.size(), expectedResult.size());

    while(!theList.empty())
    {
        EXPECT_THAT(theList.front(), expectedResult.front());
        theList.removeFront();
        expectedResult.pop_front();
    }
}

template<typename T>
void assertDLinkedListResult(DLinkedList<T>& theList, deque<T>& expectedResult)
{
    ASSERT_THAT(theList.size(), expectedResult.size());

    while(!theList.empty())
    {
        EXPECT_THAT(theList.front(), expectedResult.front());
        theList.removeFront();
        expectedResult.pop_front();
    }
}
}

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// R-3.1
TEST(GameEntry, Construct)
{
    GameEntry ge("Eric", 100);
    EXPECT_THAT(ge.getName(), Eq(string("Eric")));
    EXPECT_THAT(ge.getScore(), Eq(100));
}

TEST(Scores, AddScore)
{
    GameEntry eric("Eric", 100);
    GameEntry joe("Joe", 90);
    GameEntry bill("Bill", 110);

    Scores gameScores;
    EXPECT_THAT(gameScores.numScores(), Eq(0));
    gameScores.add(eric);
    EXPECT_THAT(gameScores.numScores(), Eq(1));
    gameScores.add(joe);
    EXPECT_THAT(gameScores.numScores(), Eq(2));
    gameScores.add(bill);
    EXPECT_THAT(gameScores.numScores(), Eq(3));

    auto firstPlace = gameScores.at(0);
    auto secondPlace = gameScores.at(1);
    auto thirdPlace = gameScores.at(2);

    EXPECT_THAT(firstPlace.getName(), Eq(bill.getName()));
    EXPECT_THAT(firstPlace.getScore(), Eq(bill.getScore()));

    EXPECT_THAT(secondPlace.getName(), Eq(eric.getName()));
    EXPECT_THAT(secondPlace.getScore(), Eq(eric.getScore()));

    EXPECT_THAT(thirdPlace.getName(), Eq(joe.getName()));
    EXPECT_THAT(thirdPlace.getScore(), Eq(joe.getScore()));
}

TEST(Scores, RemoveScore)
{
    GameEntry eric("Eric", 100);
    GameEntry joe("Joe", 90);
    GameEntry bill("Bill", 110);

    Scores gameScores;
    gameScores.add(eric);
    gameScores.add(joe);
    gameScores.add(bill);

    gameScores.remove(1);
    EXPECT_THAT(gameScores.numScores(), Eq(2));

    auto firstPlace = gameScores.at(0);
    auto secondPlace = gameScores.at(1);

    EXPECT_THAT(firstPlace.getName(), Eq(bill.getName()));
    EXPECT_THAT(firstPlace.getScore(), Eq(bill.getScore()));

    EXPECT_THAT(secondPlace.getName(), Eq(joe.getName()));
    EXPECT_THAT(secondPlace.getScore(), Eq(joe.getScore()));
}

TEST(Scores, MaxScoresForOnePlayer)
{
    Scores gameScores(10);
     // try to add one too many
    auto numEntriesToAdd = gameScores.maxEntriesPerPlayer() + 1; 
    for (auto i=0; i<numEntriesToAdd; i++)
    {
        gameScores.add({"Eric", i * 10});
    }

    EXPECT_THAT(gameScores.numScores(), Eq(gameScores.maxEntriesPerPlayer()));
}

// R-3.3
TEST(TransposeMatrix, TransposeMatrix)
{
    constexpr auto Rows = 10u;
    constexpr auto Cols = Rows;

    Matrix myMatrix(Rows, vector<float>(Cols));

    for (auto i=0u; i<Rows; i++)
    {
        for (auto j=0u; j<Cols; j++)
        {
            myMatrix[i][j] = static_cast<float>(i);
        }
    }

    cout << "original matrix" << endl;
    printMatrix(myMatrix);

    Matrix t = (myMatrix);
    transpose(t);
    cout << "transpose matrix" << endl;
    printMatrix(t);

    for (auto i=0u; i<Rows; i++)
    {
        for (auto j=0u; j<Cols; j++)
        {
            ASSERT_THAT(t[i][j], Eq(myMatrix[j][i]));
        }
    }
}

// R-3.4
TEST(RecursiveSumMatrix, RecursiveSumMatrix)
{
    constexpr auto Rows = 5u;
    constexpr auto Cols = Rows;

    Matrix myMatrix(Rows, vector<float>(Cols));

    float expectedSum = 0;
    for (auto i=0u; i<Rows; i++)
    {
        for (auto j=0u; j<Cols; j++)
        {
            myMatrix[i][j] = static_cast<float>(i);
            expectedSum += static_cast<float>(i);
        }
    }

    printMatrix(myMatrix);
    cout << "expectedSum is " << expectedSum << endl;

    auto result = recursiveSum(myMatrix);
    EXPECT_THAT(result, Eq(expectedSum));
}

TEST(SinglyLinkedList, AddAndRemove)
{
    StringLinkedList myList;
    myList.addFront("A");
    EXPECT_THAT(myList.front(), Eq(string("A")));
    myList.addFront("B");
    EXPECT_THAT(myList.front(), Eq(string("B")));
    myList.addFront("C");
    EXPECT_THAT(myList.front(), Eq(string("C")));

    myList.removeFront();
    EXPECT_THAT(myList.front(), Eq(string("B")));
    myList.removeFront();
    EXPECT_THAT(myList.front(), Eq(string("A")));
    myList.removeFront();
    EXPECT_THAT(myList.empty(), Eq(true));
}

// R-3.5
TEST(SinglyLinkedList, RecursivelyDefinedList)
{
    vector<string> items = {"Eric", "Adam", "Joe"};
    StringLinkedList myList;
    recursivelyDefineList(myList, items);

    EXPECT_THAT(myList.front(), Eq(string("Eric")));
    myList.removeFront();
    EXPECT_THAT(myList.front(), Eq(string("Adam")));
    myList.removeFront();
    EXPECT_THAT(myList.front(), Eq(string("Joe")));
    myList.removeFront();
    EXPECT_THAT(myList.empty(), Eq(true));
}

// R-3.6
TEST(SinglyLinkedList, Size)
{
    StringLinkedList myList;
    EXPECT_THAT(myList.size(), Eq(0));
    myList.addFront("A");
    myList.addFront("B");
    myList.addFront("C");
    EXPECT_THAT(myList.size(), Eq(3));
    myList.removeFront();
    myList.removeFront();
    myList.removeFront();
    EXPECT_THAT(myList.size(), Eq(0));
}

// R-3.7
TEST(SinglyLinkedList, Penultimate)
{
    StringLinkedList myList;
    myList.addFront("A");
    myList.addFront("B");
    myList.addFront("C");

    auto secondToLast = myList.penultimate();
    ASSERT_NE(secondToLast, nullptr);
    EXPECT_THAT(secondToLast->elem, Eq(string("B")));
}

// R-3.8
TEST(DoublyLinkedList, EmptyAndNotEmpty)
{
    DLinkedList<int> myList;
    EXPECT_TRUE(myList.empty());
    myList.addBack(1);
    EXPECT_FALSE(myList.empty());
}

TEST(DoublyLinkedList, AddBack)
{
    DLinkedList<int> myList;
    myList.addBack(4);
    EXPECT_THAT(myList.back(), Eq(4));
    myList.addBack(5);
    EXPECT_THAT(myList.back(), Eq(5));
    myList.addBack(6);
    EXPECT_THAT(myList.back(), Eq(6));
}

TEST(DoublyLinkedList, AddFront)
{
    DLinkedList<int> myList;
    myList.addFront(4);
    EXPECT_THAT(myList.front(), Eq(4));
    myList.addFront(5);
    EXPECT_THAT(myList.front(), Eq(5));
    myList.addFront(6);
    EXPECT_THAT(myList.front(), Eq(6));
}

TEST(DoublyLinkedList, RemoveBack)
{
    DLinkedList<int> myList;
    myList.addBack(1);
    myList.addBack(2);
    myList.addBack(3);
    myList.removeBack();
    EXPECT_THAT(myList.back(), Eq(2));
    myList.removeBack();
    EXPECT_THAT(myList.back(), Eq(1));
    myList.removeBack();
    EXPECT_TRUE(myList.empty());
}

TEST(DoublyLinkedList, RemoveFront)
{
    DLinkedList<int> myList;
    myList.addBack(1);
    myList.addBack(2);
    myList.addBack(3);
    myList.removeFront();
    EXPECT_THAT(myList.front(), Eq(2));
    myList.removeFront();
    EXPECT_THAT(myList.front(), Eq(3));
    myList.removeFront();
    EXPECT_TRUE(myList.empty());
}

// R-3.9
TEST(DoublyLinkedList, ThrowsIfCallFrontWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.front(), runtime_error);
}

TEST(DoublyLinkedList, ThrowsIfCallBackWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.back(), runtime_error);
}

TEST(DoublyLinkedList, ThrowsIfCallRemoveFrontWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.removeFront(), runtime_error);
}

TEST(DoublyLinkedList, ThrowsIfCallRemoveBackWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.removeBack(), runtime_error);
}

// R-3.10
TEST(DoublyLinkedList, MiddleNodeThrowsIfEmpty)
{
    DLinkedList<int> myList;
    EXPECT_THROW(myList.middleElement(), runtime_error);
}

TEST(DoublyLinkedList, MiddleNodeSelected)
{
    DLinkedList<int> myList;
    for (int element = 1; element<100; element++)
    {
        myList.addBack(element);
        EXPECT_THAT(myList.middleElement(), Eq((element/2) + 1));
    }
}

// R-3.11
TEST(ArrayMaxRecursive, ThrowsIfArrayEmpty)
{
    vector<int> myArray;
    EXPECT_THROW(findArrayMaximum(myArray), runtime_error);
}

TEST(ArrayMaxRecursive, FindsMaxElement)
{
    vector<int> myArray = {3, 5, -2, 7, -9};
    EXPECT_THAT(findArrayMaximum(myArray), Eq(7));
}

// R-3.14
TEST(RemoveElements, RemoveElements)
{
    vector<int> myArray = {1, 2, 3, 4, 5};
    removeRandomUntilEmpty(myArray);
    EXPECT_THAT(myArray.empty(), true);
}

// R-3.15
TEST(CircleLinkedList, Empty)
{
    CircleList<int> myList;
    EXPECT_THAT(myList.empty(), true);
    myList.add(1);
    EXPECT_THAT(myList.empty(), false);
}

TEST(CircleLinkedList, AddToList)
{
    CircleList<int> myList;
    myList.add(1);
    EXPECT_THAT(myList.front(), 1);
    EXPECT_THAT(myList.back(), 1);
    myList.add(2);
    EXPECT_THAT(myList.front(), 2);
    EXPECT_THAT(myList.back(), 1);
    myList.add(3);
    EXPECT_THAT(myList.front(), 3);
    EXPECT_THAT(myList.back(), 1);
}

TEST(CircleLinkedList, RemoveFromList)
{
    CircleList<int> myList;
    myList.add(1);
    myList.add(2);
    myList.add(3);
    EXPECT_THAT(myList.front(), 3);
    EXPECT_THAT(myList.back(), 1);

    myList.remove();
    EXPECT_THAT(myList.front(), 2);
    EXPECT_THAT(myList.back(), 1);
    myList.remove();
    EXPECT_THAT(myList.front(), 1);
    EXPECT_THAT(myList.back(), 1);
    myList.remove();
    EXPECT_THAT(myList.empty(), true);
}

// R-3.16
TEST(CirlceLinkedList, ThrowsIfAdvanceEmptyList)
{
    CircleList<int> myList;
    EXPECT_THROW(myList.advance(), runtime_error);
}

TEST(CirlceLinkedList, ThrowsIfRemoveFromEmptyList)
{
    CircleList<int> myList;
    EXPECT_THROW(myList.remove(), runtime_error);
}

// R-3.16
TEST(CircleLinkedList, CountNodes)
{
    CircleList<int> myList;
    EXPECT_THAT(myList.count(), 0ul);
    myList.add(1);
    EXPECT_THAT(myList.count(), 1ul);
    myList.add(1);
    EXPECT_THAT(myList.count(), 2ul);
    myList.remove();
    EXPECT_THAT(myList.count(), 1ul);
    myList.remove();
    EXPECT_THAT(myList.count(), 0ul);
}

// C-3.1
// when changing the values of X and O the counting trick in isWin
// will still work. As long as X != O. And the magnitude of X and Y cannot 
// be so large that multiplying it by 3 causes integer overflow / underflow. 
// Although the method of switching current player in putMark will have to change.
TEST(TicTacToeGame, PlayGame)
{
    TicTacToe game;
    game.clearBoard();
    game.putMark(0,0);
    game.putMark(1,1);
    game.putMark(0,1);
    game.putMark(0,2);
    game.putMark(2,0);
    game.putMark(1,2);
    game.putMark(2,2);
    game.putMark(2,1);
    game.putMark(1,0);
    game.printBoard();

    auto winner = game.getWinner();
    if (winner != game.Empty)
    {
        cout << " " << (winner == game.X ? "X" : "O") << " wins" << endl;
    }
    else
    {
        cout << " Tie" << endl;
    }
}

// C-3.3
TEST(FindRepeat, FindRepeat)
{
    vector<int> myArray = {1, 2, 5, 4, 5, 6};
    int repeat{};
    EXPECT_THAT(findRepeat(myArray, repeat, 2), true);
    EXPECT_THAT(repeat, 5);
}

TEST(FindRepeat, DoesNotUpdateIfNoRepeat)
{
    vector<int> myArray = {1, 2, 3, 4, 5, 6};
    int repeat = 0;
    EXPECT_THAT(findRepeat(myArray, repeat, 2), false);
    EXPECT_THAT(repeat, 0); 
}

// C-3.4
TEST(Find5Repeated, Find5Repeat)
{
    vector<int> myArray = {1, 2, 3, 3, 3, 3, 3, 4, 5};
    int repeat{};
    EXPECT_THAT(findRepeat(myArray, repeat, 5), true);
    EXPECT_THAT(repeat, 3);
}

// C-3.5
TEST(EnchantedForestGame, Winner1000Meetings)
{
    EnchantedForest game;
    EXPECT_THAT(game.gameOver(), false);
    EXPECT_THAT(game.winners().empty(), true);

    for (auto encounter=0u; encounter<=1000; encounter++)
    {
        game.meet(123, encounter);
    }

    EXPECT_THAT(game.gameOver(), true);

    const auto& winners = game.winners();
    ASSERT_THAT(winners.size(), 1);
    EXPECT_THAT(winners.front(), 123);
}

TEST(EnchantedForestGame, CantMeetYourself)
{
    EnchantedForest game;
    for (auto encounter=0u; encounter<1000; encounter++)
    {
        game.meet(1, 1);
    }

    EXPECT_THAT(game.gameOver(), false);
    EXPECT_THAT(game.winners().empty(), true);
}

TEST(EnchantedForestGame, Tie)
{
    EnchantedForest game;
    auto start = 3;
    for (auto encounter=start; encounter < start + 999; encounter++)
    {
        game.meet(1, encounter);
        game.meet(2, encounter);
    }
    game.meet(1,2);
    EXPECT_THAT(game.gameOver(), true);

    const auto& winners = game.winners();

    EXPECT_THAT(find(winners.begin(), winners.end(), 1), Ne(winners.end()));
    EXPECT_THAT(find(winners.begin(), winners.end(), 2), Ne(winners.end()));
}

TEST(RecursiveProduct, RecursiveProduct)
{
    EXPECT_THAT(recursiveProduct(2, 3), 6);
    EXPECT_THAT(recursiveProduct(6, 6), 36);
}

// C-3.7
TEST(ReverseSLinkedList, RecursiveReverseSLinkedList)
{
    StringLinkedList myList;
    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    myList.reverseRecursive();
    EXPECT_THAT(myList.front(), string("D"));
    myList.removeFront();
    EXPECT_THAT(myList.front(), string("C"));
    myList.removeFront();
    EXPECT_THAT(myList.front(), string("B"));
    myList.removeFront();
    EXPECT_THAT(myList.front(), string("A"));
    myList.removeFront();
}

// C-3.8
TEST(SinglyLinkedList, ConcatenateSLinkedList)
{
    StringLinkedList oneList;
    oneList.addFront("C");
    oneList.addFront("B");
    oneList.addFront("A");

    StringLinkedList anotherList;
    anotherList.addFront("F");
    anotherList.addFront("E");
    anotherList.addFront("D");

    oneList.concatenate(anotherList);
    EXPECT_THAT(anotherList.empty(), true);

    EXPECT_THAT(oneList.front(), string("A"));
    oneList.removeFront();
    EXPECT_THAT(oneList.front(), string("B"));
    oneList.removeFront();
    EXPECT_THAT(oneList.front(), string("C"));
    oneList.removeFront();
    EXPECT_THAT(oneList.front(), string("D"));
    oneList.removeFront();
    EXPECT_THAT(oneList.front(), string("E"));
    oneList.removeFront();
    EXPECT_THAT(oneList.front(), string("F"));
    oneList.removeFront();
}

// C-3.9
TEST(DoublyLinkedList, ConcatenateDLinkedList)
{
    DLinkedList<int> oneList;
    oneList.addBack(1);
    oneList.addBack(2);
    oneList.addBack(3);

    DLinkedList<int> anotherList;
    anotherList.addBack(4);
    anotherList.addBack(5);
    anotherList.addBack(6);

    oneList.concatenate(anotherList);
    EXPECT_THAT(anotherList.empty(), true);
}

// C-3.10
TEST(SinglyLinkedList, SwapNodesSpacedApartAndNeitherIsHead)
{
    StringLinkedList myList;

    myList.addFront("F");
    myList.addFront("E");
    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    myList.swapNodes(string("B"), string("E"));

    deque<string> expectedResult = {"A", "E", "C", "D", "B", "F"};
    assertListResult(myList, expectedResult);
}

TEST(SinglyLinkedList, SwapNodesNeighborsAndNeitherIsHead)
{
    StringLinkedList myList;

    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    myList.swapNodes(string("B"), string("C"));

    deque<string> expectedResult = {"A", "C", "B", "D"};
    assertListResult(myList, expectedResult);
}

TEST(SinglyLinkedList, SwapNodesOneIsHead)
{
    StringLinkedList myList;

    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    myList.swapNodes(string("A"), string("C"));

    deque<string> expectedResult = {"C", "B", "A", "D"};
    assertListResult(myList, expectedResult);
}

TEST(SinglyLinkedList, SwapNodesSameNode)
{
    StringLinkedList myList;

    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    myList.swapNodes(string("B"), string("B"));

    deque<string> expectedResult = {"A", "B", "C", "D"};
    assertListResult(myList, expectedResult);
}

TEST(SinglyLinkedList, SwapNodesReversedOrder)
{
    StringLinkedList myList;

    myList.addFront("F");
    myList.addFront("E");
    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    myList.swapNodes(string("E"), string("B"));

    deque<string> expectedResult = {"A", "E", "C", "D", "B", "F"};
    assertListResult(myList, expectedResult);
}

TEST(DoublyLinkedList, SwapNodes)
{
    DLinkedList<int> myList;
    myList.addBack(1);
    auto swapA = myList.backNode();
    myList.addBack(2);
    myList.addBack(3);
    auto swapB = myList.backNode();

    myList.swapNodes(swapA, swapB);

    deque<int> expectedResult = {3, 2, 1};
    assertDLinkedListResult(myList, expectedResult);
}

TEST(DoublyLinkedList, SwapNodesNeighbors)
{
    DLinkedList<int> myList;
    myList.addBack(1);
    auto swapA = myList.backNode();
    myList.addBack(2);
    auto swapB = myList.backNode();

    myList.swapNodes(swapA, swapB);

    deque<int> expectedResult = {2, 1};
    assertDLinkedListResult(myList, expectedResult);
}

TEST(DoublyLinkedList, SwapNodesSameNode)
{
    DLinkedList<int> myList;
    myList.addBack(1);
    myList.addBack(2);
    auto swapA = myList.backNode();
    myList.addBack(3);
    auto swapB = swapA;

    myList.swapNodes(swapA, swapB);

    deque<int> expectedResult = {1, 2, 3};
    assertDLinkedListResult(myList, expectedResult);
}

// C-3.11
TEST(ReverseSLinkedList, ReverseSLinkedList)
{
    StringLinkedList myList;
    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    myList.reverse();
    EXPECT_THAT(myList.front(), string("D"));
    myList.removeFront();
    EXPECT_THAT(myList.front(), string("C"));
    myList.removeFront();
    EXPECT_THAT(myList.front(), string("B"));
    myList.removeFront();
    EXPECT_THAT(myList.front(), string("A"));
    myList.removeFront();
}

// C-3.12
struct TowersOfHanoiTest : public ::testing::Test, 
                              public WithParamInterface<int>
{
    static string testName(const TestParamInfo<int>& p)
    {
        auto diskCount = p.param;
        return to_string(diskCount) + string("_disks");
    }
};

TEST_P(TowersOfHanoiTest, Solve)
{
    TowersOfHanoi game(GetParam());
    game.print();
    game.solve();
    game.print();
    EXPECT_TRUE(game.isSolved());
}

INSTANTIATE_TEST_SUITE_P(TowersOfHanoiTest, TowersOfHanoiTest,
                         Values(1, 2, 3, 4, 5, 6), &TowersOfHanoiTest::testName);

// C-3.13
TEST(ConvertStringToDigits, ConvertStringToDigits)
{
    auto result = stringToDigits("123");
    EXPECT_THAT(result, 123);
}

// C-3.14
TEST(SinglyLinkedList, CountNodes)
{
    StringLinkedList myList;
    myList.addFront("D");
    myList.addFront("C");
    myList.addFront("B");
    myList.addFront("A");

    EXPECT_THAT(myList.countNodes(), 4);
}

// C-3.15
TEST(OutputAllSubsets, OutputAllSubsets)
{
    set<int> mySet = {1, 2, 3};
    outputAllSubsets(mySet);
}

// C-3.16
TEST(FindMinMaxRecursive, FindMinMaxRecursive)
{
    vector<int> myVec = {1, 5, 3, 4, 2};
    int min{};
    int max{};
    findMinMax(myVec, min, max);

    EXPECT_THAT(min, 1);
    EXPECT_THAT(max, 5);
}

// C-3.17
TEST(SumOfEarlier2, SumOfEarlier2)
{
    vector<int> myVec = {1, 2};
    EXPECT_FALSE(containsSumOf2Earlier(myVec));

    myVec = {1, 2, 3};
    EXPECT_TRUE(containsSumOf2Earlier(myVec));

    myVec = {1, 13, 4, 14, 27};
    EXPECT_TRUE(containsSumOf2Earlier(myVec));

    myVec = {1, 2, 4, 7, 10, 13};
    EXPECT_FALSE(containsSumOf2Earlier(myVec));
}

// C-3.18
TEST(SortEvensFirstThenOddsTest, SortEvensFirstThenOddsTest)
{
    vector<int> myVec = {1, 2, 3, 4, 5, 6, 7};
    sortEvensFirstThenOdds(myVec);
    vector<int> expectedResult = {0, 0, 0, 1, 1, 1, 1};

    for (auto i=0u; i<myVec.size(); i++)
    {
        EXPECT_THAT(myVec[i] % 2, expectedResult[i]);
    }
}

TEST(SortEvensFirstThenOddsTest, SortEvensFirstThenOddsRecursiveTest)
{
    vector<int> myVec = {1, 2, 3, 4, 5, 6, 7};
    sortEvensFirstThenOddsRecursive(myVec);
    vector<int> expectedResult = {0, 0, 0, 1, 1, 1, 1};

    for (auto i=0u; i<myVec.size(); i++)
    {
        EXPECT_THAT(myVec[i] % 2, expectedResult[i]);
    }
}

// C-3.19
TEST(ReverseStringRecursive, ReverseStringRecursive)
{
    string evenNumChars = "eric";
    reverseString(evenNumChars);
    EXPECT_THAT(evenNumChars, string("cire"));

    string oddNumChars = "bananas";
    reverseString(oddNumChars);
    EXPECT_THAT(oddNumChars, string("sananab"));
}

// C-3.20
TEST(PalendromeTest, PalendromeTest)
{
    string notPalendrome = "eric";
    string palendrome1 = "racecar";
    string palendrome2 = "gohangasalamiimalasagnahog";

    EXPECT_FALSE(isPalendrome(notPalendrome));
    EXPECT_TRUE(isPalendrome(palendrome1));
    EXPECT_TRUE(isPalendrome(palendrome2));
}

// C-3.21
TEST(MoreVowelsThanConsonants, MoreVowelsThanConsonants)
{
    string yes = "eerie";
    string no = "west";

    EXPECT_TRUE(hasMoreVowelsThanConsonants(yes));
    EXPECT_FALSE(hasMoreVowelsThanConsonants(no));
}

TEST(MoreVowelsThanConsonants, MultipleWords)
{
    string line = "one two three";
    EXPECT_FALSE(hasMoreVowelsThanConsonants(line));
}

TEST(MoreVowelsThanConsonants, YIsSometimesAVowel)
{
    string word = "yikes";
    EXPECT_FALSE(hasMoreVowelsThanConsonants(word));
    word = "byy";
    EXPECT_TRUE(hasMoreVowelsThanConsonants(word));
}

// C-3.22
TEST(SameListDifferentCursorPosition, AreSame)
{
    CircleList<int> listA;
    listA.add(1);
    listA.add(2);
    listA.add(3);

    CircleList<int> listB;
    listB.add(2);
    listB.add(3);
    listB.add(1);

    EXPECT_TRUE(sameListDifferentCursorPosition(listA, listB));
}

TEST(SameListDifferentCursorPosition, AreNotSame)
{
    CircleList<int> listA;
    listA.add(1);
    listA.add(2);
    listA.add(3);

    CircleList<int> listB;
    listB.add(5);
    listB.add(6);
    listB.add(7);

    EXPECT_FALSE(sameListDifferentCursorPosition(listA, listB));
}

// C-3.23
TEST(SplitCircleList, SplitCircleList)
{
    auto printCircleList = [](auto& list)
    {
        auto iter = list.frontNode();
        do
        {
            cout << iter->elem << " ";
            iter = iter->next;
        } while(iter != list.frontNode());
        cout << endl;
    };

    CircleList<int> myList;
    for (auto item = 1; item <=6; item++)
    {
        myList.add(item);
    }
    CircleList<int> half;

    cout << "original List: ";
    printCircleList(myList);

    split(myList, half);
    cout << "list A: ";
    printCircleList(myList);
    cout << "list B: ";
    printCircleList(half);
}

// P-3.1
TEST(AddMatrix3D, MatrixDimensions)
{
    Matrix3D myMatrix3D(4, 3, 2);
    auto dims = myMatrix3D.getDimensions();
    EXPECT_THAT(dims.rows, 4);
    EXPECT_THAT(dims.cols, 3);
    EXPECT_THAT(dims.depth, 2);
}

TEST(AddMatrix3D, Add3DMatrices)
{
    int rows = 4;
    int cols = 3;
    int depth = 2;

    Matrix3D a(rows, cols, depth);
    RandomNumberGenerator rng;

    for (auto d = 0; d < depth; d++)
    {
        for (auto r = 0; r < rows; r++)
        {
            for (auto c = 0; c < cols; c++)
            {
                a.data[d][r][c] = rng.getNumber(1, 1000);
            }
        }
    }

    auto b = a;
    auto sum = add(a, b);

    for (auto d = 0; d < depth; d++)
    {
        for (auto r = 0; r < rows; r++)
        {
            for (auto c = 0; c < cols; c++)
            {
                EXPECT_THAT(sum.data[d][r][c], 2 * a.data[d][r][c]);
            }
        }
    }
}

// P-3.2
TEST(MatrixMultiplication, Multiply)
{
    Matrix2D a(4, 3);
    Matrix2D b(3, 3);
    a.data = {{1, 0, 1},
              {2, 1, 1},
              {0, 1, 1},
              {1, 1, 2}};

    b.data = {{1, 2, 1},
              {2, 3, 1},
              {4, 2, 2}};

    Matrix2D expectedResult(4, 3);
    expectedResult.data = {{5, 4, 3},
                           {8, 9, 5},
                           {6, 5, 3},
                           {11, 9, 6}};

    auto result = a * b;
    ASSERT_THAT(result.getDimensions(), expectedResult.getDimensions());
    auto resultDims = result.getDimensions();

    for (auto i=0; i < resultDims.rows; i++)
    {
        for (auto j=0; j < resultDims.cols; j++)
        {
            ASSERT_THAT(result.data[i][j], expectedResult.data[i][j]);
        }
    }
}

TEST(MatrixMultiplication, ThrowsIfWrongDimensions)
{
    Matrix2D a(4, 3);
    Matrix2D b(2, 3);

    EXPECT_THROW(a * b, runtime_error);
}

TEST(MatrixAddition, Add)
{
    int rows = 5;
    int cols = 6;
    Matrix2D a(rows, cols);

    RandomNumberGenerator rng;
    for (auto i=0; i<rows; i++)
    {
        for (auto j=0; j<cols; j++)
        {
            a.data[i][j] = rng.getNumber(1, 1000);
        }
    }

    auto b = a;
    auto result = a + b;

    for (auto i=0; i<rows; i++)
    {
        for (auto j=0; j<cols; j++)
        {
            ASSERT_THAT(result.data[i][j], 2 * a.data[i][j]);
        }
    }
}

TEST(MatrixAddition, ThrowsIfWrongDimensions)
{
    Matrix2D a(4, 3);
    Matrix2D b(2, 3);

    EXPECT_THROW(a + b, runtime_error);
}

template<typename T>
struct ScoreListTest : public testing::Test
{
    using ElementType = T;
};

using MyTypes = testing::Types<ScoreLinkedList, ScoreDLinkedList, ScoreCLinkedList>;
TYPED_TEST_SUITE(ScoreListTest, MyTypes);

// P-3.3 --> P-3.5
TYPED_TEST(ScoreListTest, AddScoresInOrder)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(4);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));

    ASSERT_THAT(myList.numScores(), 3);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
    EXPECT_THAT(myList.at(2), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, AddScoresOutOfOrder)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(4);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("C", 90));
    myList.add(GameEntry("B", 100));

    ASSERT_THAT(myList.numScores(), 3);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
    EXPECT_THAT(myList.at(2), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, AddScoresReplaceHead)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("B", 90));
    myList.add(GameEntry("A", 100));

    ASSERT_THAT(myList.numScores(), 2);
    EXPECT_THAT(myList.at(0), GameEntry("A", 100));
    EXPECT_THAT(myList.at(1), GameEntry("B", 90));
}

TYPED_TEST(ScoreListTest, AddScoresReplaceHeadWithExtras)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(4);
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));
    myList.add(GameEntry("A", 110));

    ASSERT_THAT(myList.numScores(), 3);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
    EXPECT_THAT(myList.at(2), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, AddScoresUpToLimit)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));

    ASSERT_THAT(myList.numScores(), 3);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
    EXPECT_THAT(myList.at(2), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, AddScoresPastLimit)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));
    myList.add(GameEntry("D", 80));

    ASSERT_THAT(myList.numScores(), 3);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
    EXPECT_THAT(myList.at(2), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, AddScoresPastLimitWithReplace)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("D", 80));
    myList.add(GameEntry("C", 90));

    ASSERT_THAT(myList.numScores(), 3);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
    EXPECT_THAT(myList.at(2), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, AddScoresPastLimitWithReplaceHead)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("D", 80));
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));

    ASSERT_THAT(myList.numScores(), 3);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
    EXPECT_THAT(myList.at(2), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, RemoveMiddle)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));

    myList.remove(1);
    ASSERT_THAT(myList.numScores(), 2);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, RemoveHead)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));

    myList.remove(0);
    ASSERT_THAT(myList.numScores(), 2);
    EXPECT_THAT(myList.at(0), GameEntry("B", 100));
    EXPECT_THAT(myList.at(1), GameEntry("C", 90));
}

TYPED_TEST(ScoreListTest, RemoveTail)
{
    using ElementType  = typename TestFixture::ElementType;

    ElementType myList(3);
    myList.add(GameEntry("A", 110));
    myList.add(GameEntry("B", 100));
    myList.add(GameEntry("C", 90));

    myList.remove(2);
    ASSERT_THAT(myList.numScores(), 2);
    EXPECT_THAT(myList.at(0), GameEntry("A", 110));
    EXPECT_THAT(myList.at(1), GameEntry("B", 100));
}

// P-3.6
TEST(SummationPuzzleTest, PotPanBib)
{
    SummationPuzzle puzzle("pot", "pan", "bib");
    EXPECT_TRUE(puzzle.solve());
}

// disabled because it may take several seconds to complete
TEST(SummationPuzzleTest, DISABLED_DogCatPig)
{
    SummationPuzzle puzzle("dog", "cat", "pig");
    EXPECT_TRUE(puzzle.solve());
}

// disabled because it may take several seconds to complete
TEST(SummationPuzzleTest, DISABLED_BoyGirlBaby)
{
    SummationPuzzle puzzle("boy", "girl", "baby");
    EXPECT_TRUE(puzzle.solve());
}

// P-3.7
TEST(CipherTest, Encrypt)
{
    Cipher cipher;
    string message = "this is a secret message";
    EXPECT_THAT(message, Ne(cipher.encrypt(message)));
}

TEST(CipherTest, Decrypt)
{
    Cipher cipher;
    string message = "this is a secret message";
    EXPECT_THAT(message, cipher.decrypt(cipher.encrypt(message)));
}
