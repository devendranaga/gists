#include <iostream>

class thisobj {
    private:
        int var;
    public:
        int displayThisObj()
        {
            std::cout << "This object has value:" << this << std::endl;
            // recursively call the function itself .. creating an infinite loop
            this->displayThisObj();
        }
};

int main()
{
    thisobj obj, obj1, obj2;

    obj.displayThisObj();
    obj1.displayThisObj();
    obj2.displayThisObj();
}