#include <string>
#include <iostream>

using namespace std;

int main()
{
    string s1("12345");

	// iterator point to the beginning of the string
	string::iterator it = s1.begin();
	string s2 = s1;

	// changing it only changes s1 but not s2... something like the copy on write in linux
	*it = '0';

	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;

	return 0;
}

