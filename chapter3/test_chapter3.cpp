#include "chapter3.h"

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
    EXPECT_THAT(secondToLast->element(), Eq(string("B")));
}

// R-3.8
TEST(DLinkedList, EmptyAndNotEmpty)
{
    DLinkedList<int> myList;
    EXPECT_TRUE(myList.empty());
    myList.addBack(1);
    EXPECT_FALSE(myList.empty());
}

TEST(DLinkedList, AddBack)
{
    DLinkedList<int> myList;
    myList.addBack(4);
    EXPECT_THAT(myList.back(), Eq(4));
    myList.addBack(5);
    EXPECT_THAT(myList.back(), Eq(5));
    myList.addBack(6);
    EXPECT_THAT(myList.back(), Eq(6));
}

TEST(DLinkedList, AddFront)
{
    DLinkedList<int> myList;
    myList.addFront(4);
    EXPECT_THAT(myList.front(), Eq(4));
    myList.addFront(5);
    EXPECT_THAT(myList.front(), Eq(5));
    myList.addFront(6);
    EXPECT_THAT(myList.front(), Eq(6));
}

TEST(DLinkedList, RemoveBack)
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

TEST(DLinkedList, RemoveFront)
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
TEST(DLinkedList, ThrowsIfCallFrontWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.front(), runtime_error);
}

TEST(DLinkedList, ThrowsIfCallBackWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.back(), runtime_error);
}

TEST(DLinkedList, ThrowsIfCallRemoveFrontWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.removeFront(), runtime_error);
}

TEST(DLinkedList, ThrowsIfCallRemoveBackWhenEmpty)
{
    DLinkedList<string> myList;
    EXPECT_THROW(myList.removeBack(), runtime_error);
}