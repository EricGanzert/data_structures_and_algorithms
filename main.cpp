#include <iostream>

int main()
{
    int x{};
    int y{};
    std::cout << "Please enter 2 numbers: ";
    std::cin >> x >> y;
    int sum = x + y;
    std::cout << "The sum is " << sum << std::endl;
    return 0;
}
