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