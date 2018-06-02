#include <iostream>

namespace ns {
    typedef enum {
        ENUM_1,
        ENUM_2,
    } TestEnum_t;

	TestEnum_t te;
};

int main()
{
    ns::TestEnum_t te1 = ns::ENUM_2;
    ns::te = ns::ENUM_1;
	std::cout << "Enum1: " << ns::te << std::endl;
}

