#include <iostream>
#include <cstdint>
#include <climits>
#include <string>

int main()
{
    std::string int_str = std::to_string(4);
    std::string long_str = std::to_string(INT_MAX);
    std::string long_long_str = std::to_string(UINT_MAX);
    std::string unsigned_str = std::to_string(65535);
    std::string double_str = std::to_string(14.414);

    std::cout << "int:" << int_str << std::endl;
    std::cout << "long:" << long_str << std::endl;
    std::cout << "long long:" << long_long_str << std::endl;
    std::cout << "unsigned int:" << unsigned_str << std::endl;
    std::cout << "double str:" << double_str << std::endl;
}