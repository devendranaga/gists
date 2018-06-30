#include <iostream>

class test_class {
    public:
        test_class(int f): a1 (f) // assign f to a1
        {
        }

        int geta1()
        {
            return a1;
        }

    private:
        int a1;
};

int main()
{
    // parameterised constructor call
    test_class test(5);

    std::cout << "a1: " << test.geta1() << std::endl;
}
