#include "chapter2.h"

#include <gmock/gmock.h>

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