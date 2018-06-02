#include <iostream>
#include <vector>

class cpp_class {
    int ptr;
    public:
        cpp_class()
        {
            std::cout << "class constructor" << std::endl;
        }
        int get_ptr()
        {
            return ptr;
        }
};

int main()
{
    std::vector<cpp_class> c; // never gets called
    cpp_class c1;

    c.push_back(c1);
}

