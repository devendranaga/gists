#include <iostream>

class thisobj {
    private:
        int var;
    public:
        thisobj()
        {
            var = 4;
        }
        int getThis()
        {
            std::cout << "this val:" << this << std::endl;

            // causes recursive loop because this is class itself and calling the function itself via this indirectly
            this->getThis();
        }
};

int main()
{
    thisobj obj;

    obj.getThis();
}