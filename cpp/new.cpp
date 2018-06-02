#include <iostream>
#include <cstring>

int main()
{
    auto int_ptr = new int;
	auto int_ptr_array = new int[5];
	auto str_ptr = new char[100];

	auto int_ptr_2 = new int(2);

	struct var {
        int i;
		char str[30];
	};

	int i;

	struct var v_a = {1, "Hello"};
	struct var *v1 = new struct var(v_a);

	*int_ptr = 5;

	for (i = 0; i < 5; i ++) {
	    *(int_ptr_array + i) = i;
	}

	strcpy(str_ptr, "Hello");

	std::cout << "int:" << *int_ptr_2 << std::endl;

	std::cout << "intr_ptr:" << int_ptr << std::endl;
	std::cout << "int@ int_ptr:" << *int_ptr << std::endl;

	for (i = 0; i < 5; i ++) {
        std::cout << "* int_ptr[" << i << "]" << *(int_ptr_array + i) << std::endl;
	}

	std::cout << "string:" << str_ptr << std::endl;

	std::cout << "v_a: " << "i:" << v_a.i << "str:" << v_a.str << std::endl;
	std::cout << "v_b: " << "i:" << v1->i << "str:" << v1->str << std::endl;

	delete int_ptr;
	delete [] int_ptr_array;
	delete [] str_ptr;
}

