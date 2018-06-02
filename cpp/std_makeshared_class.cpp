#include <iostream>
#include <memory>

class makeSharedClass {
    private:
		int n;

    public:
		makeSharedClass() {
			n = 4;
		}
		// overloaded constructor
		makeSharedClass(int a) {
            n = a;
		}
		int getClass() {
		    return n;
		}
};

int main()
{
    auto var = std::make_shared<makeSharedClass>();
	auto var1 = std::make_shared<makeSharedClass>()->getClass();
	auto var2 = std::make_shared<makeSharedClass>(44);

	std::cout << "n:"<< var->getClass() << std::endl;
	std::cout << "n1:"<<var1<<std::endl;
	std::cout << "n2:"<<var2->getClass()<<std::endl;
	
}

