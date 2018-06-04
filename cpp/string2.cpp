#include <string>
#include <iostream>

int main()
{
    std::string s1("Hello DevNaga");
	std::string s2(s1, 0, 2); // take first two characters of s1
	std::string s3(s1, 2, 4); // take middle characters of s1

    std::string::const_iterator it;
    std::string::reverse_iterator rit;

	std::cout << s1 << " " << s2 <<" "<< s3 << std::endl;

    std::cout << "first char:" << s1.at(0) <<":" << s1.at(1) << std::endl;

    for (it = s1.begin(); it != s1.end(); it ++) {
        std::cout << *it << std::endl;
    }

    for (rit = s1.rbegin(); rit != s1.rend(); rit ++) {
        std::cout << *rit << std::endl;
    }

    std::cout << "front: " << s1.front() << "last: " << s1.back() << std::endl;

    std::cout << "length: " << &s1.back() - &s1.front() + 1 << std::endl;

    std::cout << "front: " << s1.at(0) << "last: " << s1.at(s1.length() - 1) << std::endl;

    s1.clear();

    std::cout << "length of s1: " << s1.length() << std::endl;

    std::string s4 = "32";
    std::string sd = "14.44";

    int s4_int;
    double sd_double;

    s4_int = std::stoi(s4);
    sd_double = std::stod(sd);

    std::cout << "integer is : " << s4_int << std::endl;
    std::cout << "integer in hex : " << std::stoi(s4, 0, 16) << std::endl;
    std::cout << "double is : " << sd_double  << std::endl;

	return 0;
}

