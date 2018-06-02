#include <string>
#include <iostream>

int main()
{
    std::string s1("Hello");
	std::string s2(s1, 0, 2); // take first two characters of s1
	std::string s3(s1, 2, 4); // take middle characters of s1

	std::cout << s1 << " " << s2 <<" "<< s3 << std::endl;

	return 0;
}

