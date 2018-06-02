#include <iostream>

namespace ContosoData
{
    class ObjectManager
    {
    public:
        void DoSomething() {
		    std::cout << "in "<<__func__ <<" "<<__LINE__ << std::endl;
		}
    };

	void Func(ObjectManager) {
        std::cout << "in "<<__func__<<" "<<__LINE__<< std::endl;
	}
}

int main()
{
#if 0 // using fully qualified names
    ContosoData::ObjectManager mgr;

	mgr.DoSomething();

	ContosoData::Func(mgr);
#else // using using directive

	using namespace ContosoData;

	ObjectManager mgr;
	mgr.DoSomething();
	Func(mgr);
#endif

    return 0;
}

