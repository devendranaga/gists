#include <iostream>
#include <cstdlib>

int main()
{
    int *ptr = (int *)malloc(4);

    *ptr = 4;

    std::cout << "ptr is:" << *ptr << std::endl;
}

