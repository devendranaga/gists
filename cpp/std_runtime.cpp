#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
	if (argc != 2) {
		throw std::runtime_error("argc is not 2");
	}
	std::cout << "number of args : " << argc << std::endl;
}


