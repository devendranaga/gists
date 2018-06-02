#include <iostream>

// namespace that's basic
namespace variable
{
    int val = 0;
}

// nested namespace
namespace dev
{
    namespace naga
    {
        int val = 1;
		//class with in namespace
        class devnaga {
            private:
                int a;
            public:
                devnaga()
                {
                    a = 2;
                }

                int getA()
                {
                    return a;
                }
        };
    }

	// declaring class object with in the namespace
	naga::devnaga p;
}

// extending namespace
namespace variable
{
    int var = 3;
}

namespace dev {
namespace naga
{
    int var = 4;
}
}

// alias of dev::naga namespace
namespace _newdev = dev::naga;

int main()
{

    // declare a class within the namespace
    dev::naga::devnaga p;

    std::cout << "val::variable:" << variable::val << "variable::var:" << variable::var << std::endl;
    std::cout << "dev::naga::val:" << dev::naga::val << "dev::naga::var:" << dev::naga::var << std::endl;
    std::cout << "getA():" << p.getA() << std::endl;
	std::cout << "getA_new():" << dev::p.getA() << std::endl;
	std::cout << "val_newdev:" << _newdev::val << std::endl;
}

