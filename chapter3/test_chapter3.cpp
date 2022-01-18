#include "chapter3.h"

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(GameEntry, Construct)
{
    GameEntry ge("Eric", 100);
    EXPECT_THAT(ge.getName(), Eq(string("Eric")));
    EXPECT_THAT(ge.getScore(), Eq(100));
}