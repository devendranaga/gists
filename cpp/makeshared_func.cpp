#include <memory>
#include <iostream>

int make_shared_func()
{
    return 4;
}

int main()
{
    auto val = std::make_shared<int>(make_shared_func());

    std::cout << "val:" << *val << std::endl;
}