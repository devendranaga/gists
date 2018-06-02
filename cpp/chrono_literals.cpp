#include <chrono>
#include <iostream>

using namespace std::literals::chrono_literals;

int main()
{
    std::cout << 23h.count() << std::endl;
}

