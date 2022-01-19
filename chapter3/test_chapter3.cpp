#include "chapter3.h"

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

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
    gameScores.add(eric);
    gameScores.add(joe);
    gameScores.add(bill);

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

    auto firstPlace = gameScores.at(0);
    auto secondPlace = gameScores.at(1);

    EXPECT_THAT(firstPlace.getName(), Eq(bill.getName()));
    EXPECT_THAT(firstPlace.getScore(), Eq(bill.getScore()));

    EXPECT_THAT(secondPlace.getName(), Eq(joe.getName()));
    EXPECT_THAT(secondPlace.getScore(), Eq(joe.getScore()));
}