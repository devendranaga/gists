#include <iostream>

class Test {
    int x;
	Test()
	{
        x = 5;
	}
};

int main()
{
    Test *t = new Test;

	std::cout << t->x;
}

