#include <iostream>

int add(int a, int b)
{
    return a + b;
}

double add(double a, double b)
{
    return a + b;
}

int main()
{
    std::cout << "add result for ints <1 and 2>:" << add(1, 2) << std::endl;
    std::cout << "add result for doubles <1.1 and 2.2>:" << add(1.1, 2.2) << std::endl;
    std::cout << "add result for a double and int <1.1 and 2>:" << add(1.1, (double)2) << std::endl;
}