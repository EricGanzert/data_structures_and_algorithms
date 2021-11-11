#include "chapter1.h"

#include <gmock/gmock.h>

using namespace testing;


int main(int argc, char **argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// P-1.1
TEST(WriteOutSentence, WriteOutSentence)
{
    writeOutSentence("I will always use object-oriented design");
}