#include <iostream>
#include <operator>

struct var {
    int a;
    int b;
    int c;
};

int main()
{
    struct var a = {1, 2, 3}, b = {4, 5, 6}, c;

    c = a + b;

    std::cout << c.a << " : " << c.b << " : " << c.c;
}

