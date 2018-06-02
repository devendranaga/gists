#include <iostream>

class obj {
    private:
        int v;
	public:
        obj()
		{
		    std::cout << "constructor called" << std::endl;
            v = 4;
		}
		~obj()
		{
            std::cout << "destructor called" << std::endl;
            v = 0;
		}
		int getVal()
		{
		    return v;
		}
};

void f1()
{
    obj o;

    std::cout <<"v:"<< o.getVal() << std::endl;
}

void f2()
{
    obj o;

	std::cout << "v:" << o.getVal() << std::endl;
}

int main()
{
    f1();
	f2();
}

