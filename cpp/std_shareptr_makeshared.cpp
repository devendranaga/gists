#include <memory>
#include <iostream>

int main()
{
    auto p = std::make_shared<int>(10);
	std::shared_ptr<int> p1(new int);
	std::shared_ptr<int> p4(new int(10));

	*p1 = 10;

	std::cout << "p:"<< *p <<std::endl;
	std::cout << "p1:"<< *p1 <<std::endl;
	std::cout << "p4:" << *p4 <<std::endl;
}

